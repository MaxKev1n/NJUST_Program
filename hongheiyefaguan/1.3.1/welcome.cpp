#include <welcome.h>


welcome::welcome(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("登录界面"));
    this->setFixedSize(400, 200);
    main = new mainform();

    number = new QLabel(this);
    number->move(70, 80);
    number->setText("人数");

    inputnum = new QLineEdit(this);
    inputnum->move(120, 80);
    inputnum->setEchoMode(QLineEdit::Normal);

    start = new QPushButton(this);
    start->move(150, 130);
    start->setText("进入游戏");
    connect(start, &QPushButton::clicked,  this, &welcome::startgame);
}


void welcome::startgame()
{
    accept();
}
