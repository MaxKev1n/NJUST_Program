#include "mainwindow.h"
#include <QApplication>
#include <tcpserver.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCPServer *mainw = new TCPServer();
    mainw->show();

    return a.exec();
}
