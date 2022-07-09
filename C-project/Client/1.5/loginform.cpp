#include <loginform.h>


loginform::loginform(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("登录界面"));
    this->setFixedSize(400, 300);



    username1 = new QLabel(this);
    username1->move(70, 130);
    username1->setText("用户名");

    username2 = new QLineEdit(this);
    username2->move(120, 130);
    username2->setEchoMode(QLineEdit::Normal);

    userpassword1 = new QLabel(this);
    userpassword1->move(80, 190);
    userpassword1->setText("密码");

    userpassword2 = new QLineEdit(this);
    userpassword2->move(120, 190);
    userpassword2->setEchoMode(QLineEdit::Password);


    loginB = new QPushButton(this);
    loginB->move(50, 250);
    loginB->setText("登录");
    connect(loginB, &QPushButton::clicked,  this, &loginform::logindb);

    esc = new QPushButton(this);
    esc->move(250, 250);
    esc->setText("退出");
    connect(esc, &QPushButton::clicked, this, &loginform::close);

    reg = new QPushButton(this);
    reg->move(150, 250);
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

        photo.loadFromData(query.value(4).toByteArray(), "JPG");

        socket1 = new QTcpSocket;
        socket1->connectToHost("47.107.48.106", 6666);

        QString path1 = QDir::currentPath();
        path1 += '/' + user;
        QDir filePath;
        if(!filePath.exists(path1)){
            bool res = filePath.mkpath(path1);
            qDebug()<<res;
        }

        QString s2 = QString("SELECT table_name FROM information_schema.TABLES WHERE table_name ='%1';").arg(user);
        query.exec(s2);
        if(!query.next()){
            query.prepare(QString("create table %1 (id int primary key, sendername varchar(30), receivername varchar(30), time varchar(30), messages varchar(30))").arg(user));
            query.exec();
        }
        else{
            query.prepare(QString("select count(*) from %1 ").arg(user));
            query.exec();
            int size;
            if(query.next())
                size = query.value(0).toInt();
            if(size != 0){
                table messages[size];
                query.prepare(QString("select * from %1 ").arg(user));
                query.exec();
                int i = 0;
                while(query.next() && i < size){
                    messages[i].sender = query.value(1).toString();
                    messages[i].receiver = query.value(2).toString();
                    messages[i].time = query.value(3).toString();
                    messages[i].msg = query.value(4).toString();
                    qDebug()<<messages[i].msg;
                    i++;
                }

                query.prepare(QString("delete from %1 ").arg(user));
                query.exec();


                QString path1 = QDir::currentPath();
                path1 += '/' + user;
                QString path2 = QString("/ChatRecord.db");
                path2 = path1 + path2;
                path2 = QDir::toNativeSeparators(path2);
                qDebug()<<path2;
                QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
                database.setDatabaseName(path2);
                if(database.open()){
                    QSqlQuery query2;
                    for(int i = 0;i < size;i++){
                        query2.prepare(QString("select count(*) from '%1'").arg(messages[i].sender));
                        query2.exec();
                        int size2;
                        if(query2.next())
                           size2 = query2.value(0).toInt() + 1;
                        query2.prepare(QString("INSERT INTO %1(id, sendername, receivername, time, messages) VALUES(:id, :name1, :name2, :time, :mes)").arg(messages[i].sender));
                        query2.bindValue(":id", size2);
                        query2.bindValue(":name1", messages[i].sender);
                        query2.bindValue(":name2", messages[i].receiver);
                        query2.bindValue(":time", messages[i].time);
                        query2.bindValue(":mes", messages[i].msg);
                        if(!query2.exec())
                            qDebug()<<query2.lastError();
                        else qDebug()<<"success!";
                    }
                }

            }
            db.close();


        }



        if(!socket1->waitForConnected(2000)){
            QMessageBox::about(this, tr("提示"), tr("连接服务器失败，请重试"));
        }
        else{
            QByteArray array;
            QDataStream out(&array, QIODevice::WriteOnly);
            out<<1;
            out<<username2->text();
            socket1->write(array);
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
