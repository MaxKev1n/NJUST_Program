#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <headers.h>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpSocket(QObject *parent = nullptr);
    qintptr socketdescriptor;
signals:
    void updataclient(QString, int);
    void disconnected(qintptr);
    void Address(QString);
};

struct messages{
    QString sender;
    QString receiver;
    QString msg;
    QString time;
};

inline QDataStream& operator>>(QDataStream &in, messages &p)
{
    in>>p.sender>>p.receiver>>p.msg>>p.time;
    return in;
}

inline QDataStream& operator<<(QDataStream &out, messages &p)
{
    out<<p.sender<<p.receiver<<p.msg<<p.time;
    return out;
}

#endif // TCPSOCKET_H
