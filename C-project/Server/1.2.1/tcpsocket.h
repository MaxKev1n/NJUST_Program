#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <headers.h>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpSocket(QObject *parent = nullptr);
signals:
    void updataclient(QString, int);
    void disconnected(qintptr);
    void Address(QString);
};
#endif // TCPSOCKET_H
