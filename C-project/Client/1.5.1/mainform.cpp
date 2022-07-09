#include <mainform.h>

mainform::mainform(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800, 700);

    statusBar();

    image = new QLabel(this);
    image->move(30, 50);
    image->resize(160,200);
    image->setStyleSheet("QLabel{border:2px solid #242424;}");

    exita = new QAction(tr("退出"), this);
    exita->setStatusTip(tr("退出"));
    connect(exita, &QAction::triggered, this, &mainform::exit);

    chooseimage = new QAction(tr("选择头像"), this);
    chooseimage->setStatusTip(tr("选择头像"));
    connect(chooseimage, &QAction::triggered, this, &mainform::choosei);

    m1 = menuBar()->addMenu(tr("选项"));
    m1->addAction(exita);
    m1->addAction(chooseimage);

    displaytext = new QTextBrowser(this);
    displaytext->move(250, 100);
    displaytext->resize(480, 350);
    displaytext->setStyleSheet("QTextBrowser{border-image: url(://images//chat.jpg);}");

    input = new QPlainTextEdit(this);
    input->move(250, 470);
    input->resize(480, 110);


    sendp = new QPushButton(this);
    sendp->move(630, 570);
    sendp->resize(100, 50);
    sendp->setText(tr("发送"));
    sendp->setStatusTip("发送");
    sendp->setVisible(false);
    connect(sendp, &QPushButton::clicked, this, &mainform::send);

    usocket2 = new QUdpSocket;
    usocket2->bind(66666);
    connect(usocket2, SIGNAL(readyRead()), this, SLOT(receive()));

    listWidget = new QListWidget(this);
    listWidget->show();
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->resize(200, 300);
    listWidget->move(20, 280);
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(communicate(QListWidgetItem*)));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listWidget);

    friendsname = new QLabel(this);
    friendsname->move(420, 60);

    addfriendP = new QPushButton(this);
    addfriendP->move(20, 630);
    addfriendP->setText("添加好友");
    addfriendP->setStatusTip("添加好友");
    connect(addfriendP, &QPushButton::clicked, this, &mainform::addfriends);

    dialog = new addfriend();
    connect(dialog, SIGNAL(refresh()), this, SLOT(friends()));

    cws = new QTcpServer(this);
    cws->listen(QHostAddress::Any, 6667);

    socket1 = new QTcpSocket;
    socket1->connectToHost("47.107.48.106", 6666);
    if(!socket1->waitForConnected(2000)){
        QMessageBox::about(this, tr("提示"), tr("连接服务器失败，请重试"));
    }
    connect(socket1, &QTcpSocket::readyRead, [this](){
        while(socket1->bytesAvailable() > 0){
            int length = socket1->bytesAvailable();
            QByteArray data;
            data.resize(length);
            socket1->read(data.data(), length);//接受的信息
            QDataStream in(&data, QIODevice::ReadOnly);
            int flag;
            in>>flag;
            if(flag == 1)
                friends();
        }
    });

}

void mainform::successlogin()
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out<<1;
    out<<name;
    socket1->write(array);
}

void mainform::send()
{
    QString temp = input->toPlainText();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    input->clear();

    displaytext->append("[" + name + "]" + time);
    displaytext->append(temp);
    displaytext->append("\n");

    QString path1 = QDir::currentPath();
    path1 += '/' + name;
    QString path2 = QString("/ChatRecord.db");
    path2 = path1 + path2;
    path2 = QDir::toNativeSeparators(path2);
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
    }
    else qDebug()<<database.lastError();

    if(!friendonline){
        qDebug()<<"success connect";
        messages msg;
        msg.sender = name;
        msg.receiver = friendsname->text();
        msg.msg = temp;
        msg.time = time;

        QByteArray array;
        QDataStream out(&array, QIODevice::WriteOnly);

        out<<0; //flag
        out<<msg;
        socket1->write(array);
    }
    else{
        usocket1 = new QUdpSocket;
        QHostAddress Address = QHostAddress(friendsip);
        messages msg;
        msg.sender = name;
        msg.receiver = friendsname->text();
        msg.msg = temp;
        msg.time = time;
        QByteArray array;
        QDataStream out(&array, QIODevice::WriteOnly);

        out<<msg;
        usocket1->writeDatagram(array, Address, 66666);
    }

}

void mainform::receive()
{
    QByteArray datagram;
    QDataStream in(&datagram, QIODevice::ReadOnly);
    messages msg;
    while (usocket2->hasPendingDatagrams()) {
    datagram.resize(usocket2->pendingDatagramSize());
    usocket2->readDatagram(datagram.data(), datagram.size());
    in>>msg;
    }

    if(iscommunicate){
        displaytext->append("[" + msg.receiver + "]" + msg.time);
        displaytext->append(msg.msg);
        displaytext->append("\n");
    }

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
        query.prepare(QString("select count(*) from '%1'").arg(msg.sender));
        query.exec();
        int size;
        if(query.next())
           size = query.value(0).toInt() + 1;
        qDebug()<<size;
        query.prepare(QString("INSERT INTO %1(id, sendername, receivername, time, messages) VALUES(:id, :name1, :name2, :time, :mes)").arg(msg.sender));
        query.bindValue(":id", size);
        query.bindValue(":name1", msg.sender);
        query.bindValue(":name2", msg.receiver);
        query.bindValue(":time", msg.time);
        query.bindValue(":mes", msg.msg);
        if(!query.exec())
            qDebug()<<query.lastError();
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
        while (query.next()){
            QString friendname = query.value("friends").toString();
            QString friendip;
            QSqlQuery query2;
            QPixmap i;
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
                i.loadFromData(query2.value(4).toByteArray(), "JPG");
               }
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(friendname);
            item->setIcon(QIcon(i.scaled(QSize(50, 50))));
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
    iscommunicate = true;
    sendp->setVisible(true);
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

void mainform::exit()
{
    delete this;
}

void mainform::choosei()
{
    photo = new QPixmap();

    QString fileName = QFileDialog::getOpenFileName(this, tr("open a file"), "D:/", "images(*.png *.jpeg *.bmp *.jpg)");
    if(!fileName.isEmpty()){
        qDebug()<<fileName;
    }
    fileName = QDir::toNativeSeparators(fileName);
    photo->load(fileName);

    QByteArray data;
    QFile *file = new QFile(fileName);

    file->open(QIODevice::ReadOnly);
    data = file->readAll();
    file->close();
    QVariant byte(data);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");//驱动名称;
    db.setHostName("47.107.48.106");         //数据库主机名
    db.setDatabaseName("project");   //数据库名称
    db.setPort(3306);
    db.setUserName("root");         //数据库用户名
    db.setPassword("1048271926");         //数据库密码

    if(db.open()){
        QSqlQuery query;
        query.prepare("update users set image = ? where username = ?");
        query.addBindValue(byte);
        query.addBindValue(name);
        query.exec();
    }

    image->setPixmap(*photo);

}

