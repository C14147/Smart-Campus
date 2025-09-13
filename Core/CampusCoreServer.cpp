#include "CampusCoreServer.h"

CampusCoreServer::CampusCoreServer(QObject *parent)
    : QTcpServer(parent)
{}

bool CampusCoreServer::startServer(quint16 port)
{
    return listen(QHostAddress::Any, port);
}

void CampusCoreServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(socketDescriptor);

    connect(clientSocket, &QTcpSocket::readyRead, this, &CampusCoreServer::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &CampusCoreServer::onDisconnected);
}

void CampusCoreServer::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    while (socket->bytesAvailable()) {
        QByteArray data = socket->readAll();
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(data, &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject())
            continue;

        QJsonObject json = doc.object();
        processMessage(socket, json);
    }
}

void CampusCoreServer::processMessage(QTcpSocket *socket, const QJsonObject &json)
{
    // Register client if not already
    if (!socketToId.contains(socket)) {
        registerClient(socket, json);
    }

    // Route message
    forwardMessage(json);
}

void CampusCoreServer::registerClient(QTcpSocket *socket, const QJsonObject &json)
{
    QString senderId = json.value("sender_id").toString();
    if (!senderId.isEmpty()) {
        clients[senderId] = socket;
        socketToId[socket] = senderId;
    }
}

void CampusCoreServer::forwardMessage(const QJsonObject &json)
{
    QString targetId = json.value("target_id").toString();
    QByteArray msg = QJsonDocument(json).toJson(QJsonDocument::Compact) + '\n';

    if (targetId == "all") {
        for (QTcpSocket *sock : clients.values()) {
            if (sock->state() == QAbstractSocket::ConnectedState)
                sock->write(msg);
        }
    } else if (clients.contains(targetId)) {
        QTcpSocket *targetSock = clients.value(targetId);
        if (targetSock && targetSock->state() == QAbstractSocket::ConnectedState)
            targetSock->write(msg);
    }
}

void CampusCoreServer::onDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    removeClient(socket);
    socket->deleteLater();
}

void CampusCoreServer::removeClient(QTcpSocket *socket)
{
    if (socketToId.contains(socket)) {
        QString id = socketToId.take(socket);
        clients.remove(id);
    }
}
