#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <headers.h>
#include <tcpsocket.h>
#include <messages.h>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = nullptr, int port = 6666);
    QTcpSocket *cwc;
    QStringList  strlistdata;
    QMap<qintptr, QString> m;
    QMap<qintptr, QString> namemap;
    void sendonline();

public slots:
    void isonline();
signals:
    void updataserver(QString, int);
    void listensuccess(QString);
protected:
    QList<TcpSocket *> list;
    QList<qintptr> list_tcpclient;
    virtual void incomingConnection(qintptr socketDescriptor);
};


#endif // TCPSERVER_H
