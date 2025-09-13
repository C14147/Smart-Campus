#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>

class CampusCoreServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CampusCoreServer(QObject *parent = nullptr);

    bool startServer(quint16 port = 8888);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QMap<QString, QTcpSocket*> clients; // key: client unique ID
    QMap<QTcpSocket*, QString> socketToId;
    void processMessage(QTcpSocket *socket, const QJsonObject &json);
    void forwardMessage(const QJsonObject &json);
    void registerClient(QTcpSocket *socket, const QJsonObject &json);
    void removeClient(QTcpSocket *socket);
};
