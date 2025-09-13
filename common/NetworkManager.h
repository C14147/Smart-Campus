#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    void connectToServer(const QString &host, quint16 port);
    bool sendMessage(const QJsonObject &json);

signals:
    void messageReceived(const QJsonObject &json);
    void connectionStatusChanged(bool connected);

private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError);
    void tryReconnect();

private:
    QTcpSocket *socket;
    QTimer reconnectTimer;
    QString lastHost;
    quint16 lastPort;
    QByteArray buffer;
};
