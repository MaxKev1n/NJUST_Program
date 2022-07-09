#include <mainform.h>
#include <tcpserver.h>

mainform::mainform(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800, 600);
    server = new TcpServer(this, 6666);

    display = new QTextBrowser(this);
    display->resize(800, 600);
    connect(server, &TcpServer::listensuccess, [this](QString info){
        display->append(info);
    });

    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), server, SLOT(isonline()));
    //timer->start(60000);

    udp = new QUdpSocket;
    udp->bind(QHostAddress::AnyIPv4, 6660);
    connect(udp, &QUdpSocket::readyRead, this, &mainform::receiceudp);

}

void mainform::receiceudp(){
    QByteArray datagram;
    QDataStream in(&datagram, QIODevice::ReadOnly);
    int flag;
    QString name;
    QHostAddress targetaddr;
    quint16 targetport;
    while(udp->hasPendingDatagrams()){
    datagram.resize(udp->pendingDatagramSize());
    udp->readDatagram(datagram.data(), datagram.size(), &targetaddr, &targetport);
    in>>flag>>name;
    }

    QString address = targetaddr.toString();
    QString port = QString::number(targetport);
    display->append(address + ':' + port);

    if(flag == 1){
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
        db.setHostName("47.107.48.106");         //数据库主机名
        db.setDatabaseName("project");   //数据库名称
        db.setPort(3306);
        db.setUserName("root");         //数据库用户名
        db.setPassword("1048271926");
        if(db.open()){
            QSqlQuery query;
            query.prepare("UPDATE users SET ip = ?, online = '1', port = ? WHERE username = ?");
            query.addBindValue(address);
            query.addBindValue(targetport);
            query.addBindValue(name);
            query.exec();
        }
    }
}

