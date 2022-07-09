#include "addfriend.h"

addfriend::addfriend(QDialog *parent) : QDialog(parent)
{
    this->resize(260, 150);
    this->setWindowTitle("添加好友");

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
    bool isexistfriend = true;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //驱动名称
    db.setHostName("47.107.48.106");         //数据库主机名
    db.setDatabaseName("project");   //数据库名称
    db.setPort(3306);
    db.setUserName("root");         //数据库用户名
    db.setPassword("1048271926");         //数据库密码

    QString friendname = addname->text();

    if(db.open()){
      QSqlQuery query;
      query.prepare(QString("select %1 from userfriend where user = '"+username+"'").arg(friendname));
      query.exec();
      if(query.next()){
          isexistfriend = false;
      }

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

    if(isexistfriend){
        QMessageBox::about(this, tr("提示"), tr("已存在该好友"));
        return;
    }

   if(db.open() && isexist){
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
