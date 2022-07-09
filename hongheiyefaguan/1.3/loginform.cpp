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
    next->setText(tr("继续"));

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
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(tp1(QListWidgetItem*)));

    image = new QLabel(this);
    image->move(20, 100);
    image->resize(300,300);
    image->setText("ni");
    connect(next, &QPushButton::clicked, this, &mainform::change);

    openeyes = new QPushButton(this);
    openeyes->setText("睁眼");
    openeyes->move(400, 620);
    openeyes->resize(100, 50);
    openeyes->setVisible(false);
    connect(openeyes, &QPushButton::clicked, this, &mainform::zhengyan);

    notopeneyes = new QPushButton(this);
    notopeneyes->setText("不睁眼");
    notopeneyes->move(550, 620);
    notopeneyes->resize(100, 50);
    notopeneyes->setVisible(false);
    connect(openeyes, &QPushButton::clicked, this, &mainform::notzhengyan);


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

void mainform::judge(QVector<player> p)
{
    int countred = 0, countblack = 0;
    for(int i = 0;i < p.size();i++){
        if(p[i].identity == "红牌")\
            countred++;
        else countblack++;
    }
    if(countblack == 0)
        QMessageBox::about(this, tr("提示"), tr("红牌胜利"));
    if(countred == 0)
        QMessageBox::about(this, tr("提示"), tr("黑牌胜利"));
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
    }
    std::sort(p.begin(), p.end(), cmp);
    image->setPixmap(QPixmap::fromImage(*p[0].img));

}

void mainform::toupiao(QListWidget *listWidget, QVector<player> p)
{
    for(int i = 0;i < p.size();i++){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString("%1号玩家").arg(p[i].number));
        item->setTextAlignment(Qt::AlignCenter);
        item->setSizeHint(QSize(60,30));
        listWidget->addItem(item);
        map[item->text()] = p[i].number - 1;
    }
    index = 1;
}

void mainform::zhengyan()
{
    opennumber++;
    image->setPixmap(QPixmap::fromImage(*p[index - 1].img));
    if(index == number){
        index = 1;
    }
    else{
        index++;
    }
    if(count == number){
        count = 1;
        QMessageBox::about(this, tr("提示"), tr("天亮了"));
        next->setVisible(true);
        openeyes->setVisible(false);
        notopeneyes->setVisible(false);
    }
    else{
        count++;
    }
}

void mainform::notzhengyan()
{
    image->setPixmap(QPixmap::fromImage(*p[index - 1].img));
    if(index == number){
        index = 1;
    }
    else{
        index++;
    }
    if(count == number){
        count = 1;
        QMessageBox::about(this, tr("提示"), tr("天亮了"));
        next->setVisible(true);
        openeyes->setVisible(false);
    }
    else{
        count++;
    }
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
    if(count == number){
        count = 1;
        day++;
        if(day == 1){
            count = number;
            index = number;
            QMessageBox::about(this, tr("提示"), tr("开始投票选择村长"));
            toupiao(listWidget, p);
        }
        else if(!isnight){
            QMessageBox::about(this, tr("提示"), tr("开始投票"));
            isnight = true;
            toupiao(listWidget, p);
        }
        else{
            isnight = false;
            QVector<int> tempint;
            for(int i = 0;i < 2;i++){
                tempint.push_back(i + 1);
            }
            std::random_shuffle(tempint.begin(), tempint.end());
            if(tempint[0] == 1){
                boolnight = false;
                QMessageBox::about(this, tr("提示"), tr("进入黑夜"));
                openeyes->setVisible(true);
                notopeneyes->setVisible(true);
                next->setVisible(false);
            }
            else{
                QMessageBox::about(this, tr("提示"), tr("进入红夜"));
                openeyes->setVisible(true);
                notopeneyes->setVisible(true);
                next->setVisible(false);
                boolnight = true;
            }
        }
    }
    else{
        count++;
    }
}

void mainform::tp1(QListWidgetItem *item)
{
    qDebug()<<map[item->text()];
    for(int i = 0;i < p.size();i++){
        if(p[i].number == map[item->text()] + 1)
            p[i].ballot++;
    }
    image->setPixmap(QPixmap::fromImage(*p[index - 1].img));
    index++;
    if(index - 1 == number){
        index = 1;
        QMessageBox::about(this, tr("提示"), tr("投票结束"));
        if(day == 1){
            int maxnumber = 0, max =p[0].ballot;
            for(int j = 0;j < p.size();j++){
                qDebug()<<j + 1<<"号玩家"<<p[j].ballot<<"票";
                if(p[j].ballot > max){
                    maxnumber = j;
                    max = p[j].ballot;
                }
            }
            p[maxnumber].head = true;
            p[maxnumber].img->load(":/images/村长.jpg");
            QMessageBox::about(this, tr("提示"), QString("%1号玩家成为村长").arg(p[maxnumber].number));
            listWidget->clear();
        }
        else{
            int maxnumber = 0, max =p[0].ballot;
            for(int j = 0;j < p.size();j++){
                qDebug()<<j + 1<<"号玩家"<<p[j].ballot<<"票";
                if(p[j].ballot > max){
                    maxnumber = j;
                    max = p[j].ballot;
                }
            }
            QMessageBox::about(this, tr("提示"), QString("%1号玩家死亡").arg(p[maxnumber].number));
            p.erase(p.begin() + maxnumber);
            number--;
            listWidget->clear();
            map.clear();
            judge(p);
        }
        for(int j = 0;j < p.size();j++){
            p[j].ballot = 0;
        }
    }
}

