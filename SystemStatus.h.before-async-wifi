#pragma once

#include <QObject>
#include <QVariantList>
#include <QString>

class SystemStatus : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString wifiConnection READ wifiConnection NOTIFY changed)
    Q_PROPERTY(bool wifiEnabled READ wifiEnabled NOTIFY changed)
    Q_PROPERTY(bool bluetoothEnabled READ bluetoothEnabled NOTIFY changed)
    Q_PROPERTY(QVariantList wifiNetworks READ wifiNetworks NOTIFY changed)
    Q_PROPERTY(QVariantList bluetoothDevices READ bluetoothDevices NOTIFY changed)
    Q_PROPERTY(QString actionMessage READ actionMessage NOTIFY changed)

public:
    explicit SystemStatus(QObject *parent = nullptr);

    QString wifiConnection() const { return m_wifiConnection; }
    bool wifiEnabled() const { return m_wifiEnabled; }
    bool bluetoothEnabled() const { return m_bluetoothEnabled; }
    QVariantList wifiNetworks() const { return m_wifiNetworks; }
    QVariantList bluetoothDevices() const { return m_bluetoothDevices; }
    QString actionMessage() const { return m_actionMessage; }

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void setWifiEnabled(bool enabled);
    Q_INVOKABLE void toggleWifi();
    Q_INVOKABLE bool connectWifi(const QString &ssid, const QString &password = QString());
    Q_INVOKABLE void scanWifi();
    Q_INVOKABLE void disconnectWifi();

signals:
    void changed();

private:
    QString m_wifiConnection = "Tidak terhubung";
    bool m_wifiEnabled = false;
    bool m_bluetoothEnabled = false;
    QVariantList m_wifiNetworks;
    QVariantList m_bluetoothDevices;
    QString m_actionMessage = "Status sistem siap";
};
