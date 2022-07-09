#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <headers.h>
#include <tcpsocket.h>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = nullptr, int port = 6666);
    QTcpSocket *cwc;
    QStringList  strlistdata;
public slots:
    void isonline();
signals:
    void updataserver(QString, int);
    void listensuccess(QString);
protected:
    QList<TcpSocket *> list_tcpclient;
    virtual void incomingConnection(qintptr socketDescriptor);
};


#endif // TCPSERVER_H
