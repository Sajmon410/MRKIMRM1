#include "server.h"
#include "QThread"
#include "QFile"

Server::Server(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    clientConnections = new User;
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 1234)) //port
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started.";
    }
}

void Server::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    socket->write("Hello, would you like to write or read?:");
    socket->flush();
    socket->waitForBytesWritten(3000);
    clientConnections->append(socket);
    //identifikacioni broj socketa
    qDebug() << socket->socketDescriptor()<<"socket ID";
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    test(socket);
}
//funckija obradjuje podatke na server
void Server::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    QString message = socket->readAll();
    parseMessage(message, socket);
}

void Server::disconnected()
{
    //treba izbaciti korisnika iz liste aktivnih korisnika i iz liste topica kog prati i zatvoriti socket
   QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
   removeFromClients();
   socket->close();
}

void Server::removeFromClients()
{
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    User *iter = clientConnections;
    if(iter->socket == socket)
    {
        clientConnections = iter->next;
        if (iter->next == nullptr)
        {
            clientConnections = new User;
        }
    }
    else
    {
        while(iter->next->socket != socket || iter->next == nullptr)
        {
           iter = iter->next;
        }

        if(iter->next != nullptr)
        {
            iter->next = iter->next->next;
        }
    }
}

void Server::allClientsConnected()
{
    qDebug() << "Curretnly connected clients:";
     User *clientIter = clientConnections;
     while(clientIter->next != nullptr)
     {
         qDebug() << clientIter->socket->socketDescriptor();
         clientIter = clientIter->next;
     }
     qDebug() << clientIter->socket->socketDescriptor();
}

void Server::parseMessage(QString message, QTcpSocket* socket)
{
    User *client;
    client = findClient(socket->socketDescriptor());

    if(message.compare("write") == 0)
    {
        client->mode = "write";
        socket->write("What Topic would you like to write for?:");
        socket->waitForBytesWritten(3000);
    }
    else if(message.compare("read") == 0)
    {
        client->mode = "read";
        socket->write("What Topic would you like to read?:");
        socket->waitForBytesWritten(3000);
    }
    else
    {
        if(client->topic == "Prazan Topic")
        {
            client->topic = message;
            if(client->mode == "write")
            {
                socket->write("Please Write an Update to the Topic:");
                socket->waitForBytesWritten(3000);
            }
            else
            {
                socket->write("You've succesfully subscribed to the topic, you will be informed when an update had happened");
                socket->waitForBytesWritten(3000);
            }
        }
        else if(client->topic != "Prazan Topic" && client->mode == "write")
        {
            qDebug() << message;
            writeToTopic(message, socket);
        }
    }

    qDebug() << "Client Mode Test:";
    qDebug() << client->socket->socketDescriptor();
    qDebug() << client->mode;
    qDebug() << "Client Mode Test End";

    qDebug() << "Client Topic Test:";
    qDebug() << client->socket->socketDescriptor();
    qDebug() << client->topic;
    qDebug() << "Client Topic Test End";
}

User* Server::findClient(qintptr socketDescriptor)
{
    User* iter = clientConnections;
    while(iter->socket->socketDescriptor() != socketDescriptor)
    {
        iter = iter->next;
    }
    return iter;
}

void Server::test(QTcpSocket* socket)
{
    qDebug() << "Correct Client List Test:";
    allClientsConnected();
    qDebug() << "Correct Client List Test End";

    qDebug() << "findClient Test:";
    User* client = findClient(socket->socketDescriptor());
    qDebug() << client->socket->socketDescriptor();
    qDebug() << "findClient Test End";
}

void Server::writeToTopic(QString message, QTcpSocket* socket)
{
    User* client = findClient(socket->socketDescriptor());

    QString filename= client->topic + ".txt";
    qDebug() << filename;
    QFile file( filename );
    file.resize(0);

    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << message << endl;
    }

    sendUpdate(socket);
    socket->write("Please Write an Update to the Topic:");
    socket->waitForBytesWritten(3000);
}

void Server::sendUpdate(QTcpSocket* socket)
{
    User *clientWriter = findClient(socket->socketDescriptor());
    User *clientIter = clientConnections;

    while(clientIter->next != nullptr)
    {
        if(clientIter->topic == clientWriter->topic && clientWriter != clientIter)
        {
            clientReadUpdate(clientIter);
        }
        clientIter = clientIter->next;
    }

    if(clientIter->topic == clientWriter->topic && clientWriter != clientIter)
    {
        clientReadUpdate(clientIter);
    }
}
//poruka klijentu koji cita
void Server::clientReadUpdate(User* client)
{
    QString filename = client->topic + ".txt";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "error can't read file";
    }

    QTextStream in(&file);
    QString text;

    while(!in.atEnd()) {
        text += in.readLine();
    }
    file.close();

    qDebug() << text;

    QByteArray ba = text.toLocal8Bit();
    const char *string = ba.data();
    client->socket->write(string);
    client->socket->waitForBytesWritten(3000);
}
