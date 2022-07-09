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
    list_tcpclient.append(socket->socketDescriptor());

    connect(socket, &TcpSocket::Address, [this](QString address){
        emit listensuccess(address);
    });

    connect(socket, &TcpSocket::updataclient, [this, socket](QString strInfo, int length){
        strlistdata.append(strInfo);
        m[socket->socketDescriptor()] = socket->peerAddress().toString();
        if(strlistdata.size() >= 200){
            strlistdata.clear();
        }
        Q_UNUSED(length);
    });

    connect(socket, &TcpSocket::disconnected, [this](qintptr isocket){
        for(int i = 0;i <list_tcpclient.size();i++){
            qintptr descriptor = list_tcpclient.at(i);
            qDebug()<<descriptor<<isocket;
            if(descriptor == isocket){
                list_tcpclient.removeAt(i);
                qDebug()<<":";
                QString address = m[descriptor];

                QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
                db.setHostName("47.107.48.106");         //数据库主机名
                db.setDatabaseName("project");   //数据库名称
                db.setPort(3306);
                db.setUserName("root");         //数据库用户名
                db.setPassword("1048271926");
                if(db.open()){
                    QSqlQuery query;
                    query.prepare("UPDATE users SET online = '0' WHERE ip = ?");
                    query.addBindValue(address);
                    query.exec();
                    db.close();
                }
                qDebug()<<isocket<<m[descriptor]<<"disconnected";
                return;
            }
        }
    });
}

void TcpServer::isonline()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
    db.setHostName("47.107.48.106");         //数据库主机名
    db.setDatabaseName("project");   //数据库名称
    db.setPort(3306);
    db.setUserName("root");         //数据库用户名
    db.setPassword("1048271926");
    int size = 0;
    if(db.open()){
        QSqlQuery query;
        query.prepare("select count(*) from users");
        query.exec();
        if(query.next())
           size = query.value(0).toInt();
        query.prepare("SELECT * FROM users");
        query.exec();
        qDebug()<<size;
        while(query.next() && size--){
            QString ip = query.value("ip").toString();
            QHostAddress address = QHostAddress(ip);
            qDebug()<<ip;
            cwc = new QTcpSocket;
            cwc->connectToHost(address, 6667);
            if(!cwc->waitForConnected(2000) || ip == NULL){
                QSqlQuery query2(db);
                qDebug()<<"false";
                query2.prepare("UPDATE users SET online = '0' WHERE `ip` = ?");
                query2.addBindValue(ip);
                query2.exec();
            }
            else{
                qDebug()<<"true";
                QSqlQuery query2(db);
                query2.prepare("UPDATE users SET online = '1' WHERE `ip` = ?");
                query2.addBindValue(ip);
                query2.exec();
            }
        }
    }
}

