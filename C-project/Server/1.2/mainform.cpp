#include <mainform.h>

mainform::mainform(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800, 600);
    server = new TcpServer(this, 6666);

    display = new QTextBrowser(this);
    display->resize(800, 600);
    connect(server, &TcpServer::listensuccess, [this](QString info){
        display->append(info);
    });

}

