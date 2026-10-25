#pragma once

#include <QObject>
#include <QVariantList>
#include <QString>
#include <QProcess>
#include <QTimer>
#include <QStringList>

class SystemStatus : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString wifiConnection READ wifiConnection NOTIFY changed)
    Q_PROPERTY(bool wifiEnabled READ wifiEnabled NOTIFY changed)
    Q_PROPERTY(bool bluetoothEnabled READ bluetoothEnabled NOTIFY changed)
    Q_PROPERTY(QVariantList wifiNetworks READ wifiNetworks NOTIFY changed)
    Q_PROPERTY(QVariantList bluetoothDevices READ bluetoothDevices NOTIFY changed)
    Q_PROPERTY(QString actionMessage READ actionMessage NOTIFY changed)
    Q_PROPERTY(bool wifiBusy READ wifiBusy NOTIFY changed)

public:
    explicit SystemStatus(QObject *parent = nullptr);

    QString wifiConnection() const { return m_wifiConnection; }
    bool wifiEnabled() const { return m_wifiEnabled; }
    bool bluetoothEnabled() const { return m_bluetoothEnabled; }
    QVariantList wifiNetworks() const { return m_wifiNetworks; }
    QVariantList bluetoothDevices() const { return m_bluetoothDevices; }
    QString actionMessage() const { return m_actionMessage; }
    bool wifiBusy() const { return m_wifiBusy; }

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void setWifiEnabled(bool enabled);
    Q_INVOKABLE void toggleWifi();
    Q_INVOKABLE void connectWifi(const QString &ssid, const QString &password = QString());
    Q_INVOKABLE void scanWifi();
    Q_INVOKABLE void disconnectWifi();

signals:
    void changed();
    void operationFinished(const QString &operation, bool success,
                           const QString &message, const QString &ssid,
                           bool passwordRequired);

private:
    void startCommand(const QString &program, const QStringList &arguments,
                      const QString &context, int timeoutMs = 5000);
    void handleCommandFinished(int exitCode, QProcess::ExitStatus exitStatus,
                               const QString &output, const QString &error);
    void finishOperation(const QString &operation, bool success,
                         const QString &message, const QString &ssid = QString(),
                         bool passwordRequired = false);
    bool commandSucceeded(int exitCode, QProcess::ExitStatus exitStatus) const;
    bool networkIsSecured(const QString &ssid) const;
    void continueRefresh();

    QProcess *m_process = nullptr;
    QTimer *m_timeout = nullptr;
    QString m_context;
    QString m_operation;
    QString m_pendingSsid;
    QString m_pendingPassword;
    bool m_wifiBusy = false;
    bool m_refreshRequested = false;
    int m_refreshStage = 0;

    QString m_wifiConnection = "Tidak terhubung";
    bool m_wifiEnabled = false;
    bool m_bluetoothEnabled = false;
    QVariantList m_wifiNetworks;
    QVariantList m_bluetoothDevices;
    QString m_actionMessage = "Status sistem siap";
};
