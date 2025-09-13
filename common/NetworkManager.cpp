#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &NetworkManager::onReadyRead);
    connect(socket, &QTcpSocket::connected, this, &NetworkManager::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &NetworkManager::onDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &NetworkManager::onError);

    reconnectTimer.setInterval(3000);
    reconnectTimer.setSingleShot(true);
    connect(&reconnectTimer, &QTimer::timeout, this, &NetworkManager::tryReconnect);
}

void NetworkManager::connectToServer(const QString &host, quint16 port)
{
    lastHost = host;
    lastPort = port;
    socket->connectToHost(host, port);
}

bool NetworkManager::sendMessage(const QJsonObject &json)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray data = QJsonDocument(json).toJson(QJsonDocument::Compact) + '\n';
        return socket->write(data) == data.size();
    }
    return false;
}

void NetworkManager::onReadyRead()
{
    buffer += socket->readAll();
    while (true) {
        int idx = buffer.indexOf('\n');
        if (idx < 0) break;
        QByteArray line = buffer.left(idx);
        buffer = buffer.mid(idx + 1);
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(line, &err);
        if (err.error == QJsonParseError::NoError && doc.isObject())
            emit messageReceived(doc.object());
    }
}

void NetworkManager::onConnected()
{
    emit connectionStatusChanged(true);
}

void NetworkManager::onDisconnected()
{
    emit connectionStatusChanged(false);
    reconnectTimer.start();
}

void NetworkManager::onError(QAbstractSocket::SocketError)
{
    if (socket->state() != QAbstractSocket::ConnectedState)
        reconnectTimer.start();
}

void NetworkManager::tryReconnect()
{
    if (socket->state() == QAbstractSocket::UnconnectedState)
        socket->connectToHost(lastHost, lastPort);
}
