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

    userdatabase.setDatabaseName("C:\\Users\\c1048\\Documents\\build-project-Desktop_Qt_5_9_2_MinGW_32bit-Debug\\debug\\user.db");
    if(userdatabase.open()){
        QSqlQuery query;
        qDebug()<<"ok";
        query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(name));
            if(query.next())
            {
                if(query.value(0).toInt()==0)
                {
                    qDebug()<<"no";
                    query.prepare("create table '"+name+"'(id int primary key, sendname varchar(30), resname varchar(30), time varchar(30), message varchar(30))");
                    query.exec();
                }
                else{
                    qDebug()<<"right";
                }
        }
   }


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

    QSqlDatabase senddata;
    senddata.setDatabaseName("C:\\Users\\c1048\\Documents\\build-project-Desktop_Qt_5_9_2_MinGW_32bit-Debug\\debug\\user.db");
    QSqlQuery query(senddata);
    if(senddata.open()){
        query.prepare("select count(*) from '"+name+"'");
        qDebug()<<"1";
        query.exec();
        int size;
        if(query.next())
           size = query.value(0).toInt() + 1;
        qDebug()<<size;
        query.prepare("INSERT INTO '"+name+"' VALUES ('"+size+"', '"+name+"', '"+friendsname->text()+"', '"+time+"', '"+temp+"')");
        query.exec();
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
            while(query2.next())
               {
                rec = query2.record();
                int ip = rec.indexOf("ip");
                friendip = query2.value(ip).toString();
               }
            int is = query.value("online").toInt();
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(friendname);
            item->setTextAlignment(Qt::AlignCenter);
            item->setSizeHint(QSize(60,30));
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
}

void mainform::addfriends()
{
    dialog->username = name;
    dialog->show();
}
