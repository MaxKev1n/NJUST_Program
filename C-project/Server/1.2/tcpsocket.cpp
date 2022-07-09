#include <tcpsocket.h>

TcpSocket::TcpSocket(QObject *parent) : QTcpSocket(parent)
{
    connect(this, &QTcpSocket::readyRead, [this](){
        while(this->bytesAvailable() > 0){
            int length = this->bytesAvailable();
            QByteArray data;
            data.resize(length);
            this->read(data.data(), length);

            QString address = this->peerAddress().toString();
            emit Address(address);

            QString strdata = QString::number(this->socketDescriptor());
            emit updataclient(strdata, strdata.length());
            qDebug()<<"receive success!";
        }
    });
            connect(this, &QTcpSocket::disconnected, [this](){
        emit disconnected(this->socketDescriptor());
    });
}
