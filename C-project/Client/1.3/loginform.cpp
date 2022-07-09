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
  else{
      QString s = QString("select * from users where username='"+user+"' and password='"+psd+"'");
      QSqlQuery query;
      if(query.exec(s)&&query.next()){
        QMessageBox::about(this, tr("提示"), tr("登录成功"));
        socket1 = new QTcpSocket;
        socket1->connectToHost("127.0.0.1", 6666);
        if(!socket1->waitForConnected(2000)){
            QMessageBox::about(this, tr("提示"), tr("连接服务器失败，请重试"));
        }
        else{
            socket1->write(username2->text().toUtf8());
            socket1->disconnectFromHost();

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
