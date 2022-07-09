#include <loginform.h>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


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
    loginB->move(70, 200);
    loginB->setText("登录");
    connect(loginB, &QPushButton::clicked,  this, &loginform::login);

    esc = new QPushButton(this);
    esc->move(240, 200);
    esc->setText("退出");
    connect(esc, &QPushButton::clicked, this, &loginform::close);

    socket1 =new QTcpSocket;

}

void loginform::sendmessage()
{

}

void loginform::login()
{
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName("");         //数据库主机名
   db.setDatabaseName("");     //数据库名称
   db.setUserName("");         //数据库用户名
   db.setPassword("");         //数据库密码

   QString user = username2->text();
   QString psd = userpassword2->text();

   socket1->connectToHost("127.0.0.1", 8080); //服务器ip地址及端口
   if(!socket1->waitForConnected(1000)){
       QMessageBox::about(this, tr("提示"), tr("连接服务器失败"));
       return;
   }
   else{
       if(!db.open()){
           QMessageBox::about(this, tr("提示"), tr("连接失败，请重试"));
           userpassword2->clear();
           return;
       }
       else{
           QMessageBox::about(this, tr("提示"), tr("连接成功"));
           QString s = QString("select * from User where username='"+user+"' and password='"+psd+"'");
           QSqlQuery query;
           if(query.exec(s)&&query.next()){
               QMessageBox::about(this, tr("提示"), tr("登录成功"));
               return;
           }
           else{
               QMessageBox::about(this, tr("提示"), tr("登录失败"));
               return;
           }
       }
   }
}
