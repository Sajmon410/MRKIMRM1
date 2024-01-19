#include "user.h"


User::User(QObject *parent) : QObject(parent)
{
    topic = "Prazan Topic";
    socket = nullptr;
    next = nullptr;
    mode = "read";
    flag = 1;
}

void User::append(QTcpSocket *socket)
{
    User *iter = this;

    if(flag == 1)
    {
       flag = 0;
       iter->socket = socket;
       iter->next = nullptr;
       iter->topic = "Prazan Topic";
    }
    else
    {


        while(iter->next!=nullptr)
        {
         iter = iter->next;
        }

        iter->next = new User;
        iter->next->socket = socket;
        iter->next->next = nullptr;
        iter->next->topic = "Prazan Topic";
        qDebug() << socket->socketDescriptor() << "Dodat u niz";
    }

}
