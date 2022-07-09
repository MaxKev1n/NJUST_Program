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

    playername = new QLabel(this);
    playername->move(200, 10);
    playername->resize(60, 60);

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
    night->move(120, 10);
    night->resize(60, 60);


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
    connect(notopeneyes, &QPushButton::clicked, this, &mainform::notzhengyan);


}

void mainform::send()
{
    QString tempstring = input->toPlainText();
    QString tn = QString("%1").arg(p[n - 1].number);
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
    temp = p;

}

void mainform::toupiao(QListWidget *listWidget, QVector<player> p)
{
    next->setVisible(false);
    for(int i = 0;i < temp.size();i++){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString("%1号玩家").arg(temp[i].number));
        item->setTextAlignment(Qt::AlignCenter);
        item->setSizeHint(QSize(60,30));
        listWidget->addItem(item);
        map[item->text()] = temp[i].number - 1;
    }
    index = 1;
}

void mainform::zhengyan()
{
    opennumber++;
    image->setPixmap(QPixmap::fromImage(*temp[index - 1].img));
    QString s = QString("%1号玩家").arg(temp[index - 1].number);
    playername->setText(s);
    if(index == number){

        QMessageBox *msgbox = new QMessageBox();
        msgbox->setText("天亮了，村长请选择发言顺序");
        night->setVisible(false);
        msgbox->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        msgbox->button(QMessageBox::Yes)->setText("左侧");
        msgbox->button(QMessageBox::No)->setText("右侧");
        int result=msgbox->exec();
        if(result == QMessageBox::Yes){
            n = headnumber == 1 ? number : headnumber - 1;
            rol = false;
        }
        else{
            n = headnumber == 7 ? 1 : headnumber + 1;
            rol = true;
        }


        QString s = QString("%1号玩家").arg(p[n - 1].number);
        playername->setText(s);
        next->setVisible(true);
        openeyes->setVisible(false);
        notopeneyes->setVisible(false);

        index = 1;
    }
    else{
        index++;
    }
}

void mainform::notzhengyan()
{
    image->setPixmap(QPixmap::fromImage(*temp[index - 1].img));
    QString s = QString("%1号玩家").arg(temp[index - 1].number);
    playername->setText(s);
    if(index == number){
        index = 1;

        QMessageBox *msgbox = new QMessageBox();
        msgbox->setText("天亮了，村长请选择发言顺序");
        msgbox->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        msgbox->button(QMessageBox::Yes)->setText("左侧");
        msgbox->button(QMessageBox::No)->setText("右侧");
        int result=msgbox->exec();
        if(result == QMessageBox::Yes){
            n = headnumber == 1 ? number : headnumber - 1;
            rol = false;
        }
        else{
            n = headnumber == number ? 1 : headnumber + 1;
            rol = true;
        }

        QString s = QString("%1号玩家").arg(p[n - 1].number);
        playername->setText(s);
        next->setVisible(true);
        openeyes->setVisible(false);
        notopeneyes->setVisible(false);

        index = 1;
    }
    else{
        index++;
    }
}

void mainform::change()
{
    image->setPixmap(QPixmap::fromImage(*p[n - 1].img));
    QString s = QString("%1号玩家").arg(p[n - 1].number);
    playername->setText(s);
    if(!p[n-1].life){
        QString temp = QString("%1号玩家已死亡").arg(n);
        displaytext->append(temp);
    }
    switch (rol) {
    case true:
        if(n == 1){
            n = tempnumber;
        }
        else{
            n--;
        }
        break;
    case false:
        if(n == tempnumber){
            n = 1;
        }
        else{
            n++;
        }
        break;
    }
    if(!p[n-1].life){
        QString temp = QString("%1号玩家已死亡").arg(n);
        displaytext->append(temp);
    }
    qDebug()<<index;
    qDebug()<<isnight;
    if(index == tempnumber){
        index = 1;
        day++;
        if(day == 1){
            index = tempnumber;
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
                QPixmap *pixmap = new QPixmap(":/images/黑月.jpg");
                pixmap->scaled(night->size(), Qt::KeepAspectRatio);
                night->setScaledContents(true);
                night->setPixmap(*pixmap);
                night->setVisible(true);
                openeyes->setVisible(true);
                notopeneyes->setVisible(true);
                next->setVisible(false);
            }
            else{
                QMessageBox::about(this, tr("提示"), tr("进入红夜"));
                openeyes->setVisible(true);
                QPixmap *pixmap = new QPixmap(":/images/红月.jpg");
                pixmap->scaled(night->size(), Qt::KeepAspectRatio);
                night->setScaledContents(true);
                night->setPixmap(*pixmap);
                night->setVisible(true);
                notopeneyes->setVisible(true);
                next->setVisible(false);
                boolnight = true;
            }
        }
    }
    else{
        index++;
    }
}

void mainform::tp1(QListWidgetItem *item)
{
    qDebug()<<map[item->text()];
        for(int i = 0;i < temp.size();i++){
            if(temp[i].number == map[item->text()] + 1)
                temp[i].ballot++;
        }
        image->setPixmap(QPixmap::fromImage(*temp[index - 1].img));
        index++;
        if(index - 1 == number){
            index = 1;
            QMessageBox::about(this, tr("提示"), tr("投票结束"));
            if(day == 1){
                int maxnumber = 0, max =temp[0].ballot;
                for(int j = 0;j < p.size();j++){
                    qDebug()<<j + 1<<"号玩家"<<temp[j].ballot<<"票";
                    if(temp[j].ballot > max){
                        maxnumber = j;
                        max = temp[j].ballot;
                    }
                }
                temp[maxnumber].head = true;
                temp[maxnumber].img->load(":/images/村长.jpg");
                QMessageBox::about(this, tr("提示"), QString("%1号玩家成为村长").arg(temp[maxnumber].number));
                headnumber = temp[maxnumber].number;
                qDebug()<<index;
                index = number;
                next->setVisible(true);
                listWidget->clear();
            }
            else{
                int maxnumber = 0, max =temp[0].ballot;
                for(int j = 0;j < temp.size();j++){
                    qDebug()<<j + 1<<"号玩家"<<temp[j].ballot<<"票";
                    if(temp[j].ballot > max){
                        maxnumber = j;
                        max = temp[j].ballot;
                    }
                }
                QMessageBox::about(this, tr("提示"), QString("%1号玩家死亡").arg(temp[maxnumber].number));
                next->setVisible(true);
                p[temp[maxnumber].number - 1].life = false;
                temp.erase(temp.begin() + maxnumber);
                number--;
                listWidget->clear();
                map.clear();
                judge(temp);
            }
            for(int j = 0;j < temp.size();j++){
                temp[j].ballot = 0;
            }
        }
}

