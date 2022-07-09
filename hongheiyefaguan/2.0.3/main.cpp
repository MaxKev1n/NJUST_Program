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
    switch(wel.exec()){
    case QDialog::Accepted:{
        wel.main->show();
        wel.main->number = wel.inputnum->text().toInt();
        wel.main->TotalNumber = wel.main->number;
        wel.main->start();
        return app.exec();
        break;
    }
    case QDialog::Rejected:{
        wel.main->show();
        wel.main->start2();
        return app.exec();
        break;
    }
    }

    return 0;

}
