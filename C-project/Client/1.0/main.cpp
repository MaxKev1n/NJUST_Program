#include <QApplication>
#include "loginform.h"
#include "mainform.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainform *main = new mainform();
    main->setWindowTitle("欢迎界面");

    loginform login;
     if (login.exec() == QDialog::Accepted)
       {
             main->show();
             return app.exec();
       }
             else return 0;
}
