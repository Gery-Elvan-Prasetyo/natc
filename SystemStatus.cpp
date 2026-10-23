#include "SystemStatus.h"
#include <QDebug>
#include <QProcess>
#include <QRegularExpression>
#include <QStringList>
#include <QVariantMap>

static QString runCommand(const QString &program,
                          const QStringList &arguments,
                          int timeoutMs = 2500)
{
    QProcess process;
    process.start(program, arguments);

    if (!process.waitForStarted(1000))
        return {};

    if (!process.waitForFinished(timeoutMs)) {
        process.kill();
        process.waitForFinished();
        return {};
    }

    if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0)
        return {};

    return QString::fromLocal8Bit(process.readAllStandardOutput()).trimmed();
}

static bool runCommandOk(const QString &program,
                         const QStringList &arguments,
                         int timeoutMs = 8000)
{
    QProcess process;
    process.start(program, arguments);

    if (!process.waitForStarted(1000)) {
        qWarning() << "Gagal menjalankan perintah:" << program;
        return false;
    }

    if (!process.waitForFinished(timeoutMs)) {
        process.kill();
        process.waitForFinished();

        const QString error = QString::fromLocal8Bit(
            process.readAllStandardError()).trimmed();

        qWarning().noquote()
            << program << "timeout:" << error;

        return false;
    }

    const QString error = QString::fromLocal8Bit(
        process.readAllStandardError()).trimmed();

    if (process.exitStatus() != QProcess::NormalExit ||
        process.exitCode() != 0) {
        qWarning().noquote()
            << program << "gagal:" << error;
        return false;
    }

    return true;
}

SystemStatus::SystemStatus(QObject *parent)
    : QObject(parent)
{
    refresh();
}

void SystemStatus::refresh()
{
    const QString radio = runCommand("nmcli", {"radio", "wifi"});
    m_wifiEnabled = radio == "enabled";

    const QString connection = runCommand(
        "nmcli", {"-t", "-f", "DEVICE,TYPE,STATE,CONNECTION", "device", "status"});

    m_wifiConnection = "Tidak terhubung";
    for (const QString &line : connection.split('\n', Qt::SkipEmptyParts)) {
        const QStringList fields = line.split(':');
        if (fields.size() >= 4 && fields[1] == "wifi" && fields[2] == "connected") {
            m_wifiConnection = fields.mid(3).join(':');
            break;
        }
    }

    m_wifiNetworks.clear();
    const QString networks = runCommand(
        "nmcli", {"-t", "-e", "yes", "-f", "IN-USE,SSID,SIGNAL,SECURITY",
                  "device", "wifi", "list"}, 5000);

    for (const QString &line : networks.split('\n', Qt::SkipEmptyParts)) {
        const QStringList fields = line.split(':');
        if (fields.size() < 4 || fields[1].trimmed().isEmpty())
            continue;

        QVariantMap network;
        network["name"] = fields[1];
        network["action"] = fields[0] == "*" ? "Terhubung" : fields[2] + "% sinyal";
        network["signal"] = fields[2].toInt();
        network["security"] = fields[3];
        network["connected"] = fields[0] == "*";
        m_wifiNetworks.append(network);
    }

    const QString bluetooth = runCommand("bluetoothctl", {"show"});
    m_bluetoothEnabled = bluetooth.contains("Powered: yes");

    m_bluetoothDevices.clear();
    const QString devices = runCommand("bluetoothctl", {"devices"});
    const QRegularExpression devicePattern("^Device\\s+([0-9A-Fa-f:]+)\\s+(.+)$");
    for (const QString &line : devices.split('\n', Qt::SkipEmptyParts)) {
        const auto match = devicePattern.match(line);
        if (!match.hasMatch())
            continue;

        QVariantMap device;
        device["name"] = match.captured(2);
        device["address"] = match.captured(1);
        device["action"] = "Perangkat dikenal";
        m_bluetoothDevices.append(device);
    }

    emit changed();
}

void SystemStatus::setWifiEnabled(bool enabled)
{
    const QString desired = enabled ? "on" : "off";
    if (runCommandOk("nmcli", {"radio", "wifi", desired})) {
        m_actionMessage = enabled ? "Wi-Fi diaktifkan" : "Wi-Fi dimatikan";
    } else {
        m_actionMessage = "Gagal mengubah Wi-Fi. Coba cek NetworkManager.";
    }
    refresh();
    emit changed();
}

void SystemStatus::toggleWifi()
{
    setWifiEnabled(!m_wifiEnabled);
}

bool SystemStatus::connectWifi(const QString &ssid, const QString &password)
{
    if (ssid.trimmed().isEmpty()) {
        m_actionMessage = "Nama jaringan tidak valid";
        emit changed();
        return false;
    }

    if (!m_wifiEnabled) {
        m_actionMessage = "Aktifkan Wi-Fi dulu";
        emit changed();
        return false;
    }

    bool connected = false;
    if (!password.isEmpty()) {
        connected = runCommandOk(
            "nmcli", {"device", "wifi", "connect", ssid, "password", password}, 20000);
    } else {
        // Prefer an existing saved profile, so known networks do not need a new prompt.
        connected = runCommandOk("nmcli", {"connection", "up", "id", ssid}, 15000);
        if (!connected) {
            // Also try an open network without a password.
            bool isSecured = false;
            for (const QVariant &entry : m_wifiNetworks) {
                const QVariantMap network = entry.toMap();
                if (network.value("name").toString() == ssid) {
                    const QString security = network.value("security").toString().trimmed();
                    isSecured = !security.isEmpty() && security != "--";
                    break;
                }
            }
            if (!isSecured)
                connected = runCommandOk("nmcli", {"device", "wifi", "connect", ssid}, 15000);
        }
    }

    if (connected) {
        m_actionMessage = "Berhasil terhubung ke " + ssid;
        refresh();
        emit changed();
        return true;
    }

    m_actionMessage = password.isEmpty()
        ? "Masukkan sandi Wi-Fi atau periksa jaringan: " + ssid
        : "Gagal terhubung. Periksa sandi dan coba lagi.";
    emit changed();
    return false;
}

void SystemStatus::scanWifi()
{
    if (!m_wifiEnabled) {
        m_actionMessage = "Aktifkan Wi-Fi dulu untuk memindai jaringan";
        emit changed();
        return;
    }

    if (runCommandOk("nmcli", {"device", "wifi", "rescan"}, 8000)) {
        // Give NetworkManager a brief opportunity to update its scan cache.
        runCommand("nmcli", {"-t", "-f", "SSID", "device", "wifi", "list"}, 4000);
        m_actionMessage = "Pemindaian jaringan selesai";
    } else {
        m_actionMessage = "Pemindaian gagal. Coba lagi sebentar.";
    }
    refresh();
    emit changed();
}

void SystemStatus::disconnectWifi()
{
    const QString connection = m_wifiConnection;
    if (connection == "Tidak terhubung" || connection.isEmpty()) {
        m_actionMessage = "Wi-Fi sedang tidak terhubung";
        emit changed();
        return;
    }

    if (runCommandOk("nmcli", {"connection", "down", "id", connection}, 10000))
        m_actionMessage = "Terputus dari " + connection;
    else
        m_actionMessage = "Gagal memutus koneksi Wi-Fi";

    refresh();
    emit changed();
}
