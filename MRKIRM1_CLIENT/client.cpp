#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    setSocket();
}

void Client::setSocket()
{
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(connected()), this, SLOT(connected()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->socketDescriptor();
    socket->connectToHost("127.0.0.1",1234); //lokalna adresa i port
}

void Client::connected()
{
    qDebug() << "client connected event";
}

void Client::disconnected()
{
    qDebug() << "client disconnected";
}

//bira se mod da li se prati topic ili se pise topic, ako se prati topic dodaje se klijent u listu topica na serveru
void Client::readyRead()
{
    QString message = socket->readAll();
    qDebug().noquote() << message;
    parseMessage(message);
}

void Client::parseMessage(QString message)
{
    if (message.compare("Hello, would you like to write or read?:") == 0)
    {
        writeToServer();
    }
    else if(message.compare("What Topic would you like to write for?:") == 0)
    {
        writeToServer();
    }
    else if(message.compare("What Topic would you like to read?:") == 0)
    {
        writeToServer();
    }
    else if(message.compare("Please Write an Update to the Topic:") == 0)
    {
        writeToServer();
    }
}

void Client::writeToServer()
{
    QTextStream s(stdin);
    QString value = s.readLine();
    QByteArray ba = value.toLocal8Bit();
    const char *string = ba.data();
    socket->write(string);
    socket->flush();
    socket->waitForBytesWritten(3000);
}

void Client::topicResponse()
{
    socket->waitForReadyRead();
}
