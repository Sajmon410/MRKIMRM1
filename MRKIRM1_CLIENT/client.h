#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void setSocket();
    void writeToServer();
    void topicResponse();
    void parseMessage(QString message);

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
