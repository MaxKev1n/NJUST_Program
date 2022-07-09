#include <mainform.h>

mainform::mainform(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800, 600);

    displaytext = new QTextBrowser(this);
    displaytext->move(250, 50);
    displaytext->resize(480, 350);

    input = new QTextEdit(this);
    input->move(250, 420);
    input->resize(480, 80);


    sendp = new QPushButton(this);
    sendp->move(630, 520);
    sendp->resize(100, 50);
    sendp->setText(tr("发送"));
    connect(sendp, &QPushButton::clicked, this, &mainform::send);

    usocket2 = new QUdpSocket;
    usocket2->bind(66666);
    connect(usocket2, SIGNAL(readyRead()), this, SLOT(receive()));

    listWidget = new QListWidget(this);
    listWidget->show();
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->resize(200, 300);
    listWidget->move(20, 50);
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(communicate(QListWidgetItem*)));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listWidget);

    friendsname = new QLabel(this);
    friendsname->move(420, 10);

    addfriendP = new QPushButton(this);
    addfriendP->move(20,400);
    addfriendP->setText("添加好友");
    connect(addfriendP, &QPushButton::clicked, this, &mainform::addfriends);

    dialog = new addfriend();
    connect(dialog, SIGNAL(refresh()), this, SLOT(friends()));

    cws = new QTcpServer(this);
    cws->listen(QHostAddress::Any, 6667);

}

void mainform::send()
{
    QString temp = input->toPlainText();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    input->clear();

    usocket1 = new QUdpSocket;
    QHostAddress Address = QHostAddress(friendsip);
    usocket1->writeDatagram(temp.toUtf8(), Address, 66666);

    displaytext->append("[" + name + "]" + time);
    displaytext->append(temp);
    displaytext->append("\n");

    QString path1 = QDir::currentPath();
    path1 += '/' + name;
    QString path2 = QString("/ChatRecord.db");
    path2 = path1 + path2;
    path2 = QDir::toNativeSeparators(path2);
    qDebug()<<path2;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path2);
    if(database.open()){
        QSqlQuery query;
        query.prepare(QString("select count(*) from '%1'").arg(friendsname->text()));
        query.exec();
        int size;
        if(query.next())
           size = query.value(0).toInt() + 1;
        query.prepare(QString("INSERT INTO %1(id, sendername, receivername, time, messages) VALUES(:id, :name1, :name2, :time, :mes)").arg(friendsname->text()));
        query.bindValue(":id", size);
        query.bindValue(":name1", name);
        query.bindValue(":name2", friendsname->text());
        query.bindValue(":time", time);
        query.bindValue(":mes", temp);
        if(!query.exec())
            qDebug()<<query.lastError();
        else qDebug()<<"success!";
    }
    else qDebug()<<database.lastError();

    if(!friendonline){
        QTcpSocket *toserver;
        toserver = new QTcpSocket;
        toserver->connectToHost("127.0.0.1", 6666);
        if(!toserver->waitForConnected(2000)){
            QMessageBox::about(this, tr("提示"), tr("连接服务器失败，请重试"));
        }
        else{
            qDebug()<<"success connect";
            messages msg;
            QByteArray sder = name.toUtf8();
            msg.sender = sder.data();
            QByteArray rer = friendsname->text().toUtf8();
            msg.receiver = rer.data();
            QByteArray mg = temp.toUtf8();
            msg.msg = mg.data();
            QByteArray msgdata;
            msgdata.resize(sizeof(struct messages));
            memcpy(msgdata.data(), &msg, sizeof(struct messages));

            //toserver->write(msgdata);
            toserver->write(name.toUtf8());
        }
    }

}

void mainform::receive()
{
    QByteArray datagram;
    while (usocket2->hasPendingDatagrams()) {
    datagram.resize(usocket2->pendingDatagramSize());
    usocket2->readDatagram(datagram.data(), datagram.size());
    }

    QString name = "对方";
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    displaytext->append("[" + name + "]" + time);
    displaytext->append(datagram);
    displaytext->append("\n");

    QString path1 = QDir::currentPath();
    path1 += '/' + name;
    QString path2 = QString("/ChatRecord.db");
    path2 = path1 + path2;
    path2 = QDir::toNativeSeparators(path2);
    qDebug()<<path2;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path2);
    if(database.open()){
        QSqlQuery query;
        query.prepare(QString("select count(*) from '%1'").arg(friendsname->text()));
        query.exec();
        int size;
        if(query.next())
           size = query.value(0).toInt() + 1;
        qDebug()<<size;
        query.prepare(QString("INSERT INTO %1(id, sendername, receivername, time, messages) VALUES(:id, :name1, :name2, :time, :mes)").arg(friendsname->text()));
        query.bindValue(":id", size);
        query.bindValue(":name1", friendsname->text());
        query.bindValue(":name2", name);
        query.bindValue(":time", time);
        query.bindValue(":mes", datagram);
        if(!query.exec())
            qDebug()<<query.lastError();
        else qDebug()<<"success!";
    }
    else qDebug()<<database.lastError();
}

void mainform::friends()
{
    listWidget->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");//驱动名称;
    db.setHostName("47.107.48.106");         //数据库主机名
    db.setDatabaseName("project");   //数据库名称
    db.setPort(3306);
    db.setUserName("root");         //数据库用户名
    db.setPassword("1048271926");         //数据库密码

    if(db.open()){
        QSqlQuery query(db);
        query.prepare("select * from userfriend where user = '"+name+"'");
        query.exec();
        while (query.next())
           {QString friendname = query.value("friends").toString();
            QString friendip;
            QSqlQuery query2;
            query2.prepare("select * from users where username = :sname");
            query2.bindValue(":sname",friendname);   // 绑定数据到指定的位置
            query2.exec();
            QSqlRecord rec = query.record();
            int is;
            while(query2.next())
               {
                rec = query2.record();
                int ip = rec.indexOf("ip");
                friendip = query2.value(ip).toString();
                is = query2.value(3).toInt();
               }
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(friendname);
            item->setTextAlignment(Qt::AlignCenter);
            item->setSizeHint(QSize(60,30));
            qDebug()<<is;
            switch(is){
            case 1 : {
                item->setBackgroundColor(QColor(255,255,20,255));
                break;
            }
            case 0 : {
                item->setBackgroundColor(QColor(205,1,20,255));
                break;
            }
            }
            int index = listWidget->currentRow();
            listWidget->insertItem(index + 1, item);
            map[friendname] = friendip;
           }
        db.close();
    }
}

void mainform::communicate(QListWidgetItem *item)
{
    friendsip = map[item->text()];
    friendsname->setText(item->text());
    displaytext->clear();
    friendonline = item->backgroundColor() ==  QColor(255,255,20,255) ? true : false;

    QString path1 = QDir::currentPath();
    path1 += '/' + name;
    QString path2 = QString("/ChatRecord.db");
    path2 = path1 + path2;
    path2 = QDir::toNativeSeparators(path2);
    qDebug()<<path2;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path2);
    if(!database.open())
        qDebug()<<"open wrong";
    else{
        QSqlQuery query;
        query.prepare(QString("select count(*) from sqlite_master where type='table' and name ='%1'").arg(friendsname->text()));
        int size = 0;
        if(query.next())
            size = query.value(0).toInt();
        if(size != 0){
            qDebug()<<"table exists";
        }
        else{
            query.prepare(QString("create table %1 (id int primary key, sendername varchar(30), receivername varchar(30), time varchar(30), messages varchar(30))").arg(friendsname->text()));
            if(!query.exec())
                qDebug()<<query.lastError();
            else
                qDebug()<<"Create table success!";
        }
        query.prepare(QString("select count(*) from '%1'").arg(friendsname->text()));
        query.exec();
        if(query.next())
           size = query.value(0).toInt();
        qDebug()<<size;
        size = size - 30 >= 1 ? size - 30 : 1;
        query.prepare(QString("SELECT * FROM '%1' WHERE id >= '%2'").arg(friendsname->text()).arg(size));
        query.exec();
        while(query.next()){
            QString sendername = query.value(1).toString();
            QString time = query.value(3).toString();
            QString temp = query.value(4).toString();
            displaytext->append("[" + sendername + "]" + time);
            displaytext->append(temp);
            displaytext->append("\n");
        }
    }
}

void mainform::addfriends()
{
    dialog->username = name;
    dialog->show();
}
