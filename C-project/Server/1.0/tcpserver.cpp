#include <tcpserver.h>
#include <QMessageBox>

TCPServer::TCPServer(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800, 600);

    TCPserver = new QTcpServer(this);
    if(TCPserver->listen(QHostAddress::Any, 6666)){
        connect(TCPserver, SIGNAL(newConnection()), this, SLOT(slot_newconnect()));
    }


    TCPconnectSocket = nullptr;

    display = new QTextBrowser(this);
    display->resize(800, 600);
}

void TCPServer::slot_newconnect()
{
    if(TCPserver->hasPendingConnections()){
        TCPconnectSocket = TCPserver->nextPendingConnection();
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString ip = TCPconnectSocket->peerAddress().toString();
        display->append(time + "新连接" + ip);
    }
}
