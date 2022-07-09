#include <QApplication>
#include "loginform.h"
#include "loginform.cpp"
#include <welcome.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    welcome wel;
    wel.setObjectName("dialog");
    wel.setStyleSheet("QDialog#dialog{border-image: url(://images//wlcomeimage.jpg);}");
    if (wel.exec() == QDialog::Accepted)
       {
        wel.main->show();
        wel.main->number = wel.inputnum->text().toInt();
        wel.main->TotalNumber = wel.main->number;
        wel.main->start();

             return app.exec();
       }
             else return 0;
}
