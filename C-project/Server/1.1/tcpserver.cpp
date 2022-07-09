#include <tcpserver.h>
#include <QMessageBox>

TCPServer::TCPServer(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800, 600);

    TCPserver = new QTcpServer(this);
    if(TCPserver->listen(QHostAddress::AnyIPv4, 6666)){
        connect(TCPserver, SIGNAL(newConnection()), this, SLOT(slot_newconnect()));
    }


    TCPconnectSocket = nullptr;

    display = new QTextBrowser(this);
    display->resize(800, 600);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(isonline()));
    timer->start(60000);
}

void TCPServer::slot_newconnect()
{
    if(TCPserver->hasPendingConnections()){
        TCPconnectSocket = TCPserver->nextPendingConnection();
        connect(TCPconnectSocket, SIGNAL(readyRead()), this, SLOT(slot_recvmessage()));
    }
}

void TCPServer::slot_recvmessage()
{
    QByteArray array =  TCPconnectSocket->readAll();
    resname = array;
    QString ip = TCPconnectSocket->peerAddress().toString();


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
    db.setHostName("47.107.48.106");         //数据库主机名
    db.setDatabaseName("project");   //数据库名称
    db.setPort(3306);
    db.setUserName("root");         //数据库用户名
    db.setPassword("1048271926");
    if(!db.open()){
       QMessageBox::about(this, tr("提示"), tr("连接数据库失败，请重试"));
       qDebug() <<"error_MySql:\n" << db.lastError().text();
     }
    else{
        QSqlQuery query(db);
        query.prepare("UPDATE users SET ip = ?, online = '1' WHERE username = ?");
        query.addBindValue(ip);
        query.addBindValue(resname);
        query.exec();
    }
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    display->append(time + "新连接" + ip + " " +resname);
    TCPconnectSocket->disconnectFromHost();
}

void TCPServer::isonline()
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
            cwc = new QTcpSocket;
            cwc->connectToHost(ip, 6667);
            if(!cwc->waitForConnected(2000)){
                QSqlQuery query2(db);
                qDebug()<<ip;
                query2.prepare("UPDATE users SET online = '0' WHERE `ip` = ?");
                query2.addBindValue(ip);
                query2.exec();
            }
            else{
                QSqlQuery query2(db);
                query2.prepare("UPDATE users SET online = '1' WHERE `ip` = ?");
                query2.addBindValue(ip);
                query2.exec();
            }
        }
    }
}
