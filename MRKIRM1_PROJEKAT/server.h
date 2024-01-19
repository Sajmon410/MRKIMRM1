#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "user.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    User *clientConnections;


signals:

public slots:
    void newConnection();
    void readyRead();
    void disconnected();
    void removeFromClients();
    void allClientsConnected();
    User* findClient(qintptr socketDescriptor);
    void parseMessage(QString, QTcpSocket* socket);
    void test(QTcpSocket*);
    void writeToTopic(QString message, QTcpSocket* socket);
    void sendUpdate(QTcpSocket* socket);
    void clientReadUpdate(User* client);

private:
    QTcpServer *server;
};

#endif // SERVER_H
