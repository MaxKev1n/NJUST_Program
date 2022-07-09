#include <loginform.h>

mainform::mainform(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1000, 800);

    displaytext = new QTextBrowser(this);
    displaytext->move(450, 50);
    displaytext->resize(500, 450);

    input = new QTextEdit(this);
    input->move(450, 520);
    input->resize(500, 80);


    sendp = new QPushButton(this);
    sendp->move(850, 620);
    sendp->resize(100, 50);
    sendp->setText(tr("发送"));

    next = new QPushButton(this);
    next->move(700, 620);
    next->resize(100, 50);
    next->setText(tr("下一位"));

    night = new QLabel(this);
    night->setText(nightcolor);
    QPalette pa;
    if(nightcolor == "红夜"){
        pa.setColor(QPalette::WindowText,Qt::red);
        night->setPalette(pa);
    }
    else{
        pa.setColor(QPalette::WindowText,Qt::black);
        night->setPalette(pa);
    }

    listWidget = new QListWidget(this);
    listWidget->show();
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->resize(200, 300);
    listWidget->move(20, 450);
    //connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(communicate(QListWidgetItem*)));

    image = new QLabel(this);
    image->move(20, 100);
    image->resize(300,300);
    image->setText("ni");

}

