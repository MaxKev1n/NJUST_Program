#include <loginform.h>


loginform::loginform(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("登录界面"));
    this->setFixedSize(400, 300);

    socket1 = new QTcpSocket;
    socket1->connectToHost("47.107.48.106", 6666);
    if(socket1->waitForConnected(800)){
        QMessageBox::about(this, tr("提示"), tr("连接服务器成功"));
    }
    else{
        QMessageBox::about(this, tr("提示"), tr("连接服务器失败，请重试"));
    }

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
  else{
      QMessageBox::about(this, tr("提示"), tr("连接数据库成功"));
      QString s = QString("select * from users where username='"+user+"' and password='"+psd+"'");
      QSqlQuery query;
      if(query.exec(s)&&query.next()){
        QMessageBox::about(this, tr("提示"), tr("登录成功"));
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
    displaytext->move(250, 30);
    displaytext->resize(480, 350);

    input = new QTextEdit(this);
    input->move(250, 400);
    input->resize(480, 80);

    ipinput = new QLineEdit(this);

    sendp = new QPushButton(this);
    sendp->move(630, 500);
    sendp->resize(100, 50);
    sendp->setText(tr("发送"));
    connect(sendp, &QPushButton::clicked, this, &mainform::send);

    usocket2 = new QUdpSocket;
    usocket2->bind(66666);
    connect(usocket2, SIGNAL(readyRead()), this, SLOT(receive()));

}

void mainform::send()
{
    QString temp = input->toPlainText();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    input->clear();

    usocket1 = new QUdpSocket;
    QHostAddress Address = QHostAddress(ipinput->text());
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
   }
}
