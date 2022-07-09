#include <loginform.h>


loginform::loginform(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("登录界面"));
    this->setFixedSize(400, 300);



    username1 = new QLabel(this);
    username1->move(70, 80);
    username1->setText("用户名");

    username2 = new QLineEdit(this);
    username2->move(120, 80);
    username2->setEchoMode(QLineEdit::Normal);

    userpassword1 = new QLabel(this);
    userpassword1->move(80, 130);
    userpassword1->setText("密码");

    userpassword2 = new QLineEdit(this);
    userpassword2->move(120, 130);
    userpassword2->setEchoMode(QLineEdit::Password);


    loginB = new QPushButton(this);
    loginB->move(50, 200);
    loginB->setText("登录");
    connect(loginB, &QPushButton::clicked,  this, &loginform::logindb);

    esc = new QPushButton(this);
    esc->move(250, 200);
    esc->setText("退出");
    connect(esc, &QPushButton::clicked, this, &loginform::close);

    reg = new QPushButton(this);
    reg->move(150, 200);
    reg->setText("注册");
    connect(reg, &QPushButton::clicked, this, &loginform::registerP);

}


void loginform::logindb()
{
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
   db.setHostName("47.107.48.106");         //数据库主机名
   db.setDatabaseName("project");   //数据库名称
   db.setPort(3306);
   db.setUserName("root");         //数据库用户名
   db.setPassword("1048271926");         //数据库密码

   QString user = username2->text();
   QString psd = userpassword2->text();


  if(!db.open()){
     QMessageBox::about(this, tr("提示"), tr("连接数据库失败，请重试"));
     qDebug() <<"error_MySql:\n" << db.lastError().text();
     userpassword2->clear();

   }
  else{;
      QString s = QString("select * from users where username='"+user+"' and password='"+psd+"'");
      QSqlQuery query;
      if(query.exec(s)&&query.next()){
        QMessageBox::about(this, tr("提示"), tr("登录成功"));
        socket1 = new QTcpSocket;
        socket1->connectToHost("47.107.48.106", 6666);
        if(!socket1->waitForConnected(2000)){
            QMessageBox::about(this, tr("提示"), tr("连接服务器失败，请重试"));
        }
        else{
            socket1->write(username2->text().toUtf8());
        }
        db.close();
        accept();
        }
      else{
        QMessageBox::about(this, tr("提示"), tr("登录失败"));
           }
   }
}

void loginform::registerP()
{
    regist *regwindow = new regist(this);
    regwindow->show();
}



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
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(friendname);
            item->setTextAlignment(Qt::AlignCenter);
            item->setSizeHint(QSize(60,30));
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


regist::regist(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("注册界面"));
    this->setFixedSize(400, 300);

    username1 = new QLabel(this);
    username1->move(70, 80);
    username1->setText("用户名");

    username2 = new QLineEdit(this);
    username2->move(120, 80);
    username2->setEchoMode(QLineEdit::Normal);

    userpassword1 = new QLabel(this);
    userpassword1->move(80, 130);
    userpassword1->setText("密码");

    userpassword2 = new QLineEdit(this);
    userpassword2->move(120, 130);
    userpassword2->setEchoMode(QLineEdit::Normal);

    registP = new QPushButton(this);
    registP->move(50, 200);
    registP->setText("注册");
    connect(registP, &QPushButton::clicked,  this, &regist::registdb);
}

void regist::registdb()
{
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
   db.setHostName("47.107.48.106");         //数据库主机名
   db.setDatabaseName("project");   //数据库名称
   db.setPort(3306);
   db.setUserName("root");         //数据库用户名
   db.setPassword("1048271926");         //数据库密码

   QString user = username2->text();
   QString psd = userpassword2->text();

  if(!db.open()){
     QMessageBox::about(this, tr("提示"), tr("连接数据库失败，请重试"));
     qDebug() <<"error_MySql:\n" << db.lastError().text();
     userpassword2->clear();

   }
  else{
      QMessageBox::about(this, tr("提示"), tr("连接数据库成功"));
      QSqlQuery query(db);
      query.prepare("INSERT INTO users(username, password) VALUES(?, ?)");
      query.addBindValue(user);
      query.addBindValue(psd);
      query.exec();
      QString s = QString("select * from users where username='"+user+"' and password='"+psd+"'");
      QSqlQuery query2;
      if(query2.exec(s)&&query2.next()){
          QMessageBox::about(this, tr("提示"), tr("注册成功"));
          db.close();
          accept();
          }
   }
}


addfriend::addfriend(QDialog *parent) : QDialog(parent)
{
    this->resize(260, 150);

    addname = new QLineEdit(this);
    addname->move(40, 20);

    search = new QPushButton(this);
    search->move(20, 100);
    search->setText("搜索");
    connect(search, &QPushButton::clicked, this, &addfriend::searchuser);

    add = new QPushButton(this);
    add->move(140, 100);
    add->setText("添加");
    connect(add, &QPushButton::clicked, this, &addfriend::adduser);
}

void addfriend::searchuser()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
    db.setHostName("47.107.48.106");         //数据库主机名
    db.setDatabaseName("project");   //数据库名称
    db.setPort(3306);
    db.setUserName("root");         //数据库用户名
    db.setPassword("1048271926");         //数据库密码

    QString user = addname->text();

   if(db.open()){
      qDebug()<<"ok";
      QSqlQuery query;
      QString s = QString("select * from users where username='"+user+"'");
      query.exec(s);
      if(query.next()){
          QMessageBox::about(this, tr("提示"), tr("存在该用户"));
          db.close();
      }
      else{
          QMessageBox::about(this, tr("提示"), tr("不存在该用户"));
          db.close();
      }
    }
}

void addfriend::adduser()
{
    bool isexist;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
    db.setHostName("47.107.48.106");         //数据库主机名
    db.setDatabaseName("project");   //数据库名称
    db.setPort(3306);
    db.setUserName("root");         //数据库用户名
    db.setPassword("1048271926");         //数据库密码

    QString friendname = addname->text();

    if(db.open()){
      QSqlQuery query;
      QString s = QString("select * from users where username='"+friendname+"'");
      query.exec(s);

      if(username == friendname){
          QMessageBox::about(this, tr("警告"), tr("不允许添加本人"));
          isexist = false;
          return;
      }
      if(query.next()){
          isexist = true;
      }
      else{
          QMessageBox::about(this, tr("提示"), tr("不存在该用户"));
          isexist = false;
      }
    }

   if(db.open()&&isexist){
      QSqlQuery query(db);
      int size = 0;
      query.prepare("select count(*) from userfriend");
      query.exec();
      if(query.next())
         size = query.value(0).toInt() + 1;
      query.prepare("INSERT INTO userfriend(id, user, friends) VALUES(?, ?, ?)");
      query.addBindValue(size);
      qDebug()<<size<<username<<friendname;
      query.addBindValue(username);
      query.addBindValue(friendname);
      query.exec();
      QMessageBox::about(this, tr("提示"), tr("添加成功"));
      emit refresh();
    }
   db.close();
}
