#include <welcome.h>


welcome::welcome(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("登录界面"));
    this->setFixedSize(400, 200);

    main = new mainform();
    main->setObjectName("mainwindow");
    main->setStyleSheet("QMainWindow#mainwindow{border-image: url(://images//backgroundimage.jpg);}");

    number = new QLabel(this);
    number->move(70, 80);
    number->setText("人数");

    inputnum = new QLineEdit(this);
    inputnum->move(120, 80);
    inputnum->setEchoMode(QLineEdit::Normal);
    inputnum->setValidator(new QIntValidator(100,999,this));

    start = new QPushButton(this);
    start->move(122, 125);
    start->resize(158, 51);
    start->setStyleSheet("QPushButton{border-image: url(://images//start.jpg);}");
    connect(start, &QPushButton::clicked,  this, &welcome::startgame);
}




void welcome::startgame()
{
    accept();
}

void welcome::paintEvent(QPaintEvent *) {
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
