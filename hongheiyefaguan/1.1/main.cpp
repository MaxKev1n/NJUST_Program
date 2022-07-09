#include <QApplication>
#include "loginform.h"
#include "loginform.cpp"
#include <welcome.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    welcome wel;
    if (wel.exec() == QDialog::Accepted)
       {     mainform *main = new mainform();
             main->setWindowTitle("欢迎界面");
             main->number = wel.inputnum->text().toInt();
             main->show();
             return app.exec();
       }
             else return 0;
}
