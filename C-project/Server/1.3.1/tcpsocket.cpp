#include <tcpsocket.h>

TcpSocket::TcpSocket(QObject *parent) : QTcpSocket(parent)
{
    connect(this, &QTcpSocket::readyRead, [this](){
        while(this->bytesAvailable() > 0){
            int length = this->bytesAvailable();
            QByteArray data;
            data.resize(length);
            this->read(data.data(), length);//接受的信息
            QDataStream in(&data, QIODevice::ReadOnly);
            messages msg;
            QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
            db.setHostName("47.107.48.106");         //数据库主机名
            db.setDatabaseName("project");   //数据库名称
            db.setPort(3306);
            db.setUserName("root");         //数据库用户名
            db.setPassword("1048271926");
            if(db.open()){
                int flag;
                in>>flag;
                switch (flag) {
                case 0:{
                    in>>msg;
                    qDebug()<<msg.sender<<msg.receiver<<msg.msg<<msg.time;
                    QString s2 = QString("select * from sys.tables where name='"+msg.receiver+"'");
                    QSqlQuery query;
                    query.exec(s2);
                    if(!query.next()){
                        query.prepare(QString("create table %1 (id int primary key, sendername varchar(30), receivername varchar(30), time varchar(30), messages varchar(30))").arg(msg.receiver));
                        query.exec();
                    }
                    query.prepare(QString("select count(*) from %1").arg(msg.receiver));
                    query.exec();
                    int size2;
                    if(query.next())
                       size2 = query.value(0).toInt() + 1;
                    query.prepare(QString("INSERT INTO %1(id, sendername, receivername, time, messages) VALUES(?, ?, ?, ?, ?)").arg(msg.receiver));
                    query.addBindValue(size2);
                    query.addBindValue(msg.sender);
                    query.addBindValue(msg.receiver);
                    query.addBindValue(msg.time);
                    query.addBindValue(msg.msg);
                    query.exec();
                    break;
                }
                case 1:{
                    QString address = this->peerAddress().toString();
                    emit Address(address);
                    QString resname;
                    in>>resname;

                    if(!db.open()){
                       qDebug() <<"error_MySql:\n" << db.lastError().text();
                     }
                    else{
                        QSqlQuery query(db);
                        query.prepare("UPDATE users SET ip = ?, online = '1' WHERE username = ?");
                        query.addBindValue(address);
                        query.addBindValue(resname);
                        query.exec();
                    }

                    break;
                }
                }
                db.close();
            }



            QString strdata = QString::number(this->socketDescriptor());
            socketdescriptor = this->socketDescriptor();
            emit updataclient(strdata, strdata.length());
        }
    });
            connect(this, &QTcpSocket::disconnected, [this](){
                qDebug()<<socketdescriptor;
        emit disconnected(socketdescriptor);
    });
}
