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
    connect(sendp, &QPushButton::clicked, this, &mainform::send);

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
    connect(next, &QPushButton::clicked, this, &mainform::change);

}

void mainform::send()
{
    QString tempstring = input->toPlainText();
    QString tn = QString("%1").arg(p[index - 1].number);
    input->clear();
    displaytext->append("[" + tn + "]");
    displaytext->append(tempstring);
    displaytext->append("\n");
}

bool cmp(player a, player b){
    return a.number < b.number;
}

void mainform::start()
{
    QVector<int> tempint;
    for(int i = 0;i < number;i++){
        tempint.push_back(i + 1);
    }

    std::random_shuffle(tempint.begin(), tempint.end());
    for(int i = 0;i < number;i++){
        player temp;
        p.push_back(temp);
        p[i].number = tempint[i];
        p[i].img = new QImage;
        p[i].img->load(":/images/平民.jpg");
        if(p[i].number % 2 == 0)
            p[i].identity = "红牌";
        else p[i].identity = "黑牌";
        qDebug()<<p[i].number;
    }
    std::sort(p.begin(), p.end(), cmp);
    image->setPixmap(QPixmap::fromImage(*p[0].img));

}


void mainform::change()
{
    image->setPixmap(QPixmap::fromImage(*p[index - 1].img));
    if(index == number){
        index = 1;
    }
    else{
        index++;
    }
    //QMessageBox::about(this, tr("提示"), tr("开始投票选择村长"));
    if(count == number){
        count = 1;
        day++;
        if(day == 1)
            QMessageBox::about(this, tr("提示"), tr("开始投票选择村长"));
        else{
            QVector<int> tempint;
            for(int i = 0;i < 2;i++){
                tempint.push_back(i + 1);
            }
            std::random_shuffle(tempint.begin(), tempint.end());
            if(tempint[0] == 1){
                boolnight = false;
                QMessageBox::about(this, tr("提示"), tr("进入黑夜"));
            }
            else{
                QMessageBox::about(this, tr("提示"), tr("进入红夜"));
                boolnight = true;
            }
        }
    }
    else{
        count++;
    }
}

