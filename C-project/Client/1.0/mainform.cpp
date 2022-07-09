#include <mainform.h>

mainform::mainform(QWidget *parent) : QMainWindow(parent)
{
    welcome = new QLabel(this);
    welcome->setText("欢迎");
}
