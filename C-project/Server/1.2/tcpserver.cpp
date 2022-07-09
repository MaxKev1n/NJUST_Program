#include <tcpserver.h>
#include <tcpsocket.h>
#include <mainform.h>

TcpServer::TcpServer(QObject *parent, int port) : QTcpServer(parent)
{
    this->listen(QHostAddress::AnyIPv4, port);
    if(this->isListening()){
        qDebug()<<"listen success!";
    }

}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    TcpSocket *socket = new TcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    list_tcpclient.append(socket);

    connect(socket, &TcpSocket::Address, [this](QString address){
        emit listensuccess(address);
    });

    connect(socket, &TcpSocket::updataclient, [this](QString strInfo, int length){
        strlistdata.append(strInfo);
        if(strlistdata.size() >= 200){
            strlistdata.clear();
        }
        Q_UNUSED(length);
    });

    connect(socket, &TcpSocket::disconnected, [this](int isocket){
        for(int i = 0;i <list_tcpclient.size();i++){
            QTcpSocket *temp = list_tcpclient.at(i);
            if(temp->socketDescriptor() == isocket){
                list_tcpclient.removeAt(i);
                qDebug()<<"disconnected";
                return;
            }
        }
    });
}
