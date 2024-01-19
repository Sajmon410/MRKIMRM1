#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    QString topic;
    QTcpSocket *socket;
    User *next = nullptr;
    QString mode;
    bool flag;
    void append(QTcpSocket *socket);

signals:

public slots:
};

#endif // USER_H
