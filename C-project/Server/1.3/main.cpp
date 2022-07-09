#include "mainwindow.h"
#include <QApplication>
#include <mainform.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainform *main = new mainform();
    main->setWindowTitle("欢迎界面");
    main->show();

    return a.exec();
}
