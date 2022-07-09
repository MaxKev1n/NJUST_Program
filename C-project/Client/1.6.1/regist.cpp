#include "regist.h"

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
    QString user = username2->text();
    QString psd = userpassword2->text();
    if(user == NULL){
        QMessageBox::about(this, tr("提示"), tr("用户名为空，请重试"));
        return;
    }
    if(psd == NULL){
        QMessageBox::about(this, tr("提示"), tr("密码为空，请重试"));
        return;
    }
    if((user[0] < 'a' || user[0] > 'z') && (user[0] < 'A' || user[0] > 'Z')){
        QMessageBox::about(this, tr("提示"), tr("用户名首字符请为字母，请重试"));
        return;
    }

   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
   db.setHostName("47.107.48.106");         //数据库主机名
   db.setDatabaseName("project");   //数据库名称
   db.setPort(3306);
   db.setUserName("root");         //数据库用户名
   db.setPassword("1048271926");         //数据库密码

  if(!db.open()){
     QMessageBox::about(this, tr("提示"), tr("连接数据库失败，请重试"));
     qDebug() <<"error_MySql:\n" << db.lastError().text();
     userpassword2->clear();

   }
  else{
      QMessageBox::about(this, tr("提示"), tr("连接数据库成功"));
      QSqlQuery query(db);
      QString s = QString("select * from users where username='"+user+"'");
      QSqlQuery query2;
      if(query2.exec(s)&&query2.next()){
          QMessageBox::about(this, tr("提示"), tr("注册失败，已存在该用户"));
          db.close();
          accept();
          return;
       }
      query.prepare("INSERT INTO users(username, password) VALUES(?, ?)");
      query.addBindValue(user);
      query.addBindValue(psd);
      query.exec();
      s = QString("select * from users where username='"+user+"' and password='"+psd+"'");
      if(query2.exec(s)&&query2.next()){
          QMessageBox::about(this, tr("提示"), tr("注册成功"));
          db.close();
          accept();
          }
      else{
          QMessageBox::about(this, tr("提示"), tr("注册失败"));
      }
   }
}
