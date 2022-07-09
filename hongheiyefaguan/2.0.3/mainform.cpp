#include <mainform.h>

mainform::mainform(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800, 600);

    displaytext = new QTextBrowser(this);
    displaytext->move(250, 30);
    displaytext->resize(480, 350);

    input = new QTextEdit(this);
    input->move(250, 400);
    input->resize(480, 80);

    sendp = new QPushButton(this);
    sendp->move(630, 500);
    sendp->resize(100, 50);
    sendp->setText(tr("发送"));
    connect(sendp, &QPushButton::clicked, this, &mainform::send);

}

void mainform::send()
{
    QString temp = input->toPlainText();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString name = "我";
    input->clear();



    displaytext->append("[" + name + "]" + time);
    displaytext->append(temp);
    displaytext->append("\n");

}
