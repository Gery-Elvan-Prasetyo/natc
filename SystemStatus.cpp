#include "SystemStatus.h"

#include <QRegularExpression>
#include <QStringList>
#include <QVariantMap>
#include <QDebug>

SystemStatus::SystemStatus(QObject *parent)
    : QObject(parent), m_timeout(new QTimer(this))
{
    m_timeout->setSingleShot(true);
    connect(m_timeout, &QTimer::timeout, this, [this]() {
        if (!m_process)
            return;
        m_context += "-timeout";
        m_process->kill();
    });
    refresh();
}

bool SystemStatus::commandSucceeded(int exitCode, QProcess::ExitStatus exitStatus) const
{
    return exitStatus == QProcess::NormalExit && exitCode == 0;
}

void SystemStatus::startCommand(const QString &program, const QStringList &arguments,
                                const QString &context, int timeoutMs)
{
    if (m_process) {
        m_actionMessage = "Operasi sistem masih berjalan";
        emit changed();
        return;
    }

    m_context = context;
    m_process = new QProcess(this);
    QProcess *process = m_process;
    connect(process, &QProcess::finished, this,
            [this, process](int code, QProcess::ExitStatus status) {
        if (process != m_process)
            return;
        m_timeout->stop();
        const QString output = QString::fromLocal8Bit(process->readAllStandardOutput()).trimmed();
        const QString error = QString::fromLocal8Bit(process->readAllStandardError()).trimmed();
        m_process = nullptr;
        handleCommandFinished(code, status, output, error);
        process->deleteLater();
        if (m_refreshRequested && !m_process) {
            m_refreshRequested = false;
            refresh();
        }
    });
    connect(process, &QProcess::errorOccurred, this,
            [this, process](QProcess::ProcessError error) {
        if (process != m_process || error != QProcess::FailedToStart)
            return;
        m_timeout->stop();
        const QString output = QString::fromLocal8Bit(process->readAllStandardOutput()).trimmed();
        const QString errorText = QString::fromLocal8Bit(process->readAllStandardError()).trimmed();
        m_process = nullptr;
        handleCommandFinished(-1, QProcess::CrashExit, output, errorText);
        process->deleteLater();
        if (m_refreshRequested) {
            m_refreshRequested = false;
            refresh();
        }
    });
    process->start(program, arguments);
    m_timeout->start(timeoutMs);
}

void SystemStatus::refresh()
{
    if (m_process) {
        m_refreshRequested = true;
        return;
    }
    m_refreshStage = 0;
    continueRefresh();
}

void SystemStatus::continueRefresh()
{
    switch (m_refreshStage) {
    case 0:
        startCommand("nmcli", {"radio", "wifi"}, "refresh-radio", 2500);
        break;
    case 1:
        startCommand("nmcli", {"-t", "-f", "DEVICE,TYPE,STATE,CONNECTION", "device", "status"}, "refresh-devices", 3000);
        break;
    case 2:
        startCommand("nmcli", {"-t", "-e", "yes", "-f", "IN-USE,SSID,SIGNAL,SECURITY", "device", "wifi", "list"}, "refresh-networks", 5000);
        break;
    case 3:
        startCommand("bluetoothctl", {"show"}, "refresh-bt-show", 2500);
        break;
    case 4:
        startCommand("bluetoothctl", {"devices"}, "refresh-bt-devices", 2500);
        break;
    default:
        emit changed();
        return;
    }
}

void SystemStatus::handleCommandFinished(int exitCode, QProcess::ExitStatus exitStatus,
                                          const QString &output, const QString &error)
{
    const QString context = m_context;
    const bool timedOut = context.endsWith("-timeout");
    const QString baseContext = timedOut ? context.left(context.size() - 8) : context;
    const bool ok = commandSucceeded(exitCode, exitStatus) && !timedOut;
    if (!ok && !error.isEmpty())
        qWarning().noquote() << baseContext << error;

    if (baseContext.startsWith("refresh-")) {
        if (baseContext == "refresh-radio") {
            if (ok && (output == "enabled" || output == "disabled"))
                m_wifiEnabled = output == "enabled";
        } else if (baseContext == "refresh-devices") {
            if (ok) {
                QString connectionName = "Tidak terhubung";
                for (const QString &line : output.split('\n', Qt::SkipEmptyParts)) {
                    const QStringList fields = line.split(':');
                    if (fields.size() >= 4 && fields[1] == "wifi" && fields[2] == "connected") {
                        connectionName = fields.mid(3).join(':');
                        break;
                    }
                }
                m_wifiConnection = connectionName;
            }
        } else if (baseContext == "refresh-networks") {
            if (ok) {
                QVariantList networks;
                for (const QString &line : output.split('\n', Qt::SkipEmptyParts)) {
                    const QStringList fields = line.split(':');
                    if (fields.size() < 4 || fields[1].trimmed().isEmpty())
                        continue;
                    QVariantMap network;
                    network["name"] = fields[1];
                    network["action"] = fields[0] == "*" ? "Terhubung" : fields[2] + "% sinyal";
                    network["signal"] = fields[2].toInt();
                    network["security"] = fields[3];
                    network["connected"] = fields[0] == "*";
                    networks.append(network);
                }
                m_wifiNetworks = networks;
            }
        } else if (baseContext == "refresh-bt-show") {
            if (ok)
                m_bluetoothEnabled = output.contains("Powered: yes");
        } else if (baseContext == "refresh-bt-devices") {
            if (ok) {
                QVariantList devices;
                const QRegularExpression pattern("^Device\\s+([0-9A-Fa-f:]+)\\s+(.+)$");
                for (const QString &line : output.split('\n', Qt::SkipEmptyParts)) {
                    const auto match = pattern.match(line);
                    if (!match.hasMatch())
                        continue;
                    QVariantMap device;
                    device["name"] = match.captured(2);
                    device["address"] = match.captured(1);
                    device["action"] = "Perangkat dikenal";
                    devices.append(device);
                }
                m_bluetoothDevices = devices;
            }
        }
        ++m_refreshStage;
        emit changed();
        continueRefresh();
        return;
    }

    if (baseContext == "wifi-toggle") {
        const bool desired = m_pendingPassword == "on";
        m_pendingPassword.clear();
        finishOperation("toggle", ok,
            ok ? (desired ? "Wi-Fi diaktifkan" : "Wi-Fi dimatikan")
               : "Gagal mengubah Wi-Fi. Coba cek NetworkManager.");
    } else if (baseContext == "wifi-scan") {
        if (ok) {
            m_actionMessage = "Pemindaian jaringan selesai";
            m_refreshRequested = true;
            finishOperation("scan", true, m_actionMessage);
        } else {
            finishOperation("scan", false, "Pemindaian gagal. Coba lagi sebentar.");
        }
    } else if (baseContext == "wifi-connect-saved") {
        if (ok) {
            finishOperation("connect", true, "Berhasil terhubung ke " + m_pendingSsid, m_pendingSsid);
        } else if (networkIsSecured(m_pendingSsid)) {
            finishOperation("connect", false, "Masukkan sandi Wi-Fi: " + m_pendingSsid, m_pendingSsid, true);
        } else {
            startCommand("nmcli", {"device", "wifi", "connect", m_pendingSsid}, "wifi-connect-open", 15000);
        }
    } else if (baseContext == "wifi-connect-open" || baseContext == "wifi-connect-password") {
        if (ok)
            finishOperation("connect", true, "Berhasil terhubung ke " + m_pendingSsid, m_pendingSsid);
        else
            finishOperation("connect", false,
                m_pendingPassword.isEmpty() ? "Gagal terhubung ke jaringan: " + m_pendingSsid
                                            : "Gagal terhubung. Periksa sandi dan coba lagi.",
                m_pendingSsid);
    } else if (baseContext == "wifi-disconnect") {
        finishOperation("disconnect", ok,
            ok ? "Terputus dari " + m_pendingSsid : "Gagal memutus koneksi Wi-Fi", m_pendingSsid);
    }
}

bool SystemStatus::networkIsSecured(const QString &ssid) const
{
    for (const QVariant &entry : m_wifiNetworks) {
        const QVariantMap network = entry.toMap();
        if (network.value("name").toString() == ssid) {
            const QString security = network.value("security").toString().trimmed();
            return !security.isEmpty() && security != "--";
        }
    }
    return true;
}

void SystemStatus::finishOperation(const QString &operation, bool success,
                                   const QString &message, const QString &ssid,
                                   bool passwordRequired)
{
    m_actionMessage = message;
    m_wifiBusy = false;
    emit changed();
    emit operationFinished(operation, success, message, ssid, passwordRequired);
    if (success || operation == "scan" || operation == "toggle" || operation == "disconnect")
        m_refreshRequested = true;
}

void SystemStatus::setWifiEnabled(bool enabled)
{
    if (m_wifiBusy || m_process) {
        m_actionMessage = "Tunggu operasi Wi-Fi selesai";
        emit changed();
        return;
    }
    m_wifiBusy = true;
    m_pendingPassword = enabled ? "on" : "off";
    m_actionMessage = enabled ? "Mengaktifkan Wi-Fi…" : "Mematikan Wi-Fi…";
    emit changed();
    startCommand("nmcli", {"radio", "wifi", m_pendingPassword}, "wifi-toggle", 8000);
}

void SystemStatus::toggleWifi()
{
    setWifiEnabled(!m_wifiEnabled);
}

void SystemStatus::connectWifi(const QString &ssid, const QString &password)
{
    if (ssid.trimmed().isEmpty()) {
        finishOperation("connect", false, "Nama jaringan tidak valid", ssid);
        return;
    }
    if (!m_wifiEnabled) {
        finishOperation("connect", false, "Aktifkan Wi-Fi dulu", ssid);
        return;
    }
    if (m_wifiBusy || m_process) {
        m_actionMessage = "Tunggu operasi Wi-Fi selesai";
        emit changed();
        return;
    }

    m_wifiBusy = true;
    m_pendingSsid = ssid;
    m_pendingPassword = password;
    m_actionMessage = "Menghubungkan ke " + ssid + "…";
    emit changed();
    if (!password.isEmpty()) {
        startCommand("nmcli", {"device", "wifi", "connect", ssid, "password", password},
                     "wifi-connect-password", 20000);
    } else {
        startCommand("nmcli", {"connection", "up", "id", ssid}, "wifi-connect-saved", 15000);
    }
}

void SystemStatus::scanWifi()
{
    if (!m_wifiEnabled) {
        finishOperation("scan", false, "Aktifkan Wi-Fi dulu untuk memindai jaringan");
        return;
    }
    if (m_wifiBusy || m_process) {
        m_actionMessage = "Tunggu operasi Wi-Fi selesai";
        emit changed();
        return;
    }
    m_wifiBusy = true;
    m_actionMessage = "Memindai jaringan Wi-Fi…";
    emit changed();
    startCommand("nmcli", {"device", "wifi", "rescan"}, "wifi-scan", 8000);
}

void SystemStatus::disconnectWifi()
{
    const QString connection = m_wifiConnection;
    if (connection == "Tidak terhubung" || connection.isEmpty()) {
        finishOperation("disconnect", false, "Wi-Fi sedang tidak terhubung");
        return;
    }
    if (m_wifiBusy || m_process) {
        m_actionMessage = "Tunggu operasi Wi-Fi selesai";
        emit changed();
        return;
    }
    m_wifiBusy = true;
    m_pendingSsid = connection;
    m_actionMessage = "Memutus koneksi Wi-Fi…";
    emit changed();
    startCommand("nmcli", {"connection", "down", "id", connection}, "wifi-disconnect", 10000);
}
