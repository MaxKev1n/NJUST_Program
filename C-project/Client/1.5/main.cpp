#include <QApplication>
#include "loginform.h"
#include "addfriend.h"
#include "mainform.h"
#include "regist.h"
#include "loginform.cpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //QSqlDatabase userdatabase = QSqlDatabase::addDatabase("QSQLITE");
    //userdatabase.setDatabaseName(QApplication::applicationDirPath()+"/user.db");
    //userdatabase.setDatabaseName("C:\\Users\\c1048\\Documents\\build-project-Desktop_Qt_5_9_2_MinGW_32bit-Debug\\debug\\user.db");//本地数据库路径

    loginform login;
    login.setObjectName("dialog");
    login.setStyleSheet("QDialog#dialog{border-image: url(://images//login.jpg);}");
    if (login.exec() == QDialog::Accepted)
       {     mainform *main = new mainform();
             main->image->setPixmap(login.photo);
             main->image->setScaledContents(true);
             main->setObjectName("mainform");
             main->setStyleSheet("QMainWindow#mainform{border-image: url(://images//mainform.jpg);}");
             main->setWindowTitle("欢迎界面");
             main->name = login.username2->text();
             main->show();
             main->friends();
       }
    return app.exec();
}
