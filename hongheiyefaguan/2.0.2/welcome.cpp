#include <welcome.h>


welcome::welcome(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("登录界面"));
    this->setFixedSize(400, 250);

    main = new mainform();
    main->setObjectName("mainwindow");
    main->setStyleSheet("QMainWindow#mainwindow{border-image: url(://images//backgroundimage.jpg);}");

    number = new QLabel(this);
    number->move(70, 80);
    number->setText("人数");
    number->setStyleSheet("QLabel{font-family:SimHei;color: rgb(255, 215, 0);}");

    inputnum = new QLineEdit(this);
    inputnum->move(120, 80);
    inputnum->setEchoMode(QLineEdit::Normal);
    inputnum->setValidator(new QIntValidator(100,999,this));

    start = new QPushButton(this);
    start->move(122, 125);
    start->resize(158, 51);
    start->setStyleSheet("QPushButton{border-image: url(://images//start.jpg);border-radius:7px;}");
    connect(start, &QPushButton::clicked,  this, &welcome::startgame);

    ReadGame = new QPushButton(this);
    ReadGame->move(122, 190);
    ReadGame->resize(158, 45);
    ReadGame->setText("查看存档");
    ReadGame->setStyleSheet("QPushButton{background:#FFFAFA;border-radius:7px;}");
    connect(ReadGame, &QPushButton::clicked, [this](){
        dialog->show();
        dialog->begin();
    });

    dialog = new savedialog(this);
    connect(dialog, &savedialog::OK, this, &welcome::Read);


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

void welcome::Read(int x)
{
    QString path1 = QDir::currentPath();
    path1 += QString("/save%1.txt").arg(x);
    QFile file(path1);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<< "Cannot open file for writing: "
                  <<qPrintable(file.errorString());
        return;
    }
    else{
        QDataStream in(&file);
        in>>main->gamesave;
        QVector<player> p;
        QVector<player> temp;
        int n1, n2;
        in>>n1;
        for(int i = 0;i < n1;i++){
            player tmp;
            in>>tmp.identitynum>>tmp.number>>tmp.head>>tmp.ballot>>tmp.life;
            p.push_back(tmp);
        }
        in>>n2;
        for(int i = 0;i < n2;i++){
            player tmp;
            in>>tmp.identitynum>>tmp.number>>tmp.head>>tmp.ballot>>tmp.life;
            temp.push_back(tmp);
        }
        start2(main->gamesave, p, temp);
    }
}

void welcome::start2(Save s,QVector<player> p, QVector<player> temp)
{
    main->stage = s.stage;
    main->TotalNumber = s.TotalNumber;
    main->number = s.number;
    main->sendp->setVisible(s.sendp);
    main->next->setVisible(s.next);
    main->night->setVisible(s.night);
    main->nightcolor = s.nightcolor;
    main->listWidget->setVisible(s.listWidget);
    main->image->setVisible(s.image);
    main->openeyes->setVisible(s.openeyes);
    main->notopeneyes->setVisible(s.notopeneyes);
    main->playername->setVisible(s.playername);
    main->boolnight = s.boolnight;  //红true，黑false
    main->index = s.index;
    main->day = s.day;
    main->isnight = s.isnight;
    main->map = s.map;
    main->opennumber = s.opennumber;
    main->n = s.n;
    main->headnumber = s.headnumber;
    main->rol = s.rol; //tr,fl
    main->countred = s.countred;
    main->countblack = s.countblack;
    main->finish = s.finish;
    for(int i = 0;i < temp.size();i++){
        player tmp;
        tmp = temp[i];
        tmp.number = temp[i].number;
        tmp.identitynum = temp[i].identitynum;
        tmp.img = new QImage;
        main->temp.push_back(tmp);
    }
    for(int i = 0;i < p.size();i++){
        player tmp;
        tmp = p[i];
        tmp.number = p[i].number;
        tmp.identitynum = p[i].identitynum;
        tmp.img = new QImage;
        main->p.push_back(tmp);
    }

    reject();

}
