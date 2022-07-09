#include <QApplication>
#include "loginform.h"
#include "loginform.cpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainform *main = new mainform();
    main->setWindowTitle("欢迎界面");

    loginform login;
    if (login.exec() == QDialog::Accepted)
       {
             main->name = login.username2->text();
             main->show();
             return app.exec();
       }
             else return 0;
}
