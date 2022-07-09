#include <savedialog.h>

savedialog::savedialog(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("提示"));
    this->setFixedSize(300, 220);

    listWidget = new QListWidget(this);
    listWidget->show();
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->resize(200, 200);
    listWidget->move(10, 10);
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(choose(QListWidgetItem*)));
}

void savedialog::begin(){
    listWidget->clear();
    QString path1 = QDir::currentPath();
    int i = 1;
    while(1){
        QString path2 = QString("/save%1.txt").arg(i);
        QString fullpath = path1 + path2;
        QFileInfo fileInfo(fullpath);
        if(fileInfo.isFile()){
            i++;
            continue;
        }
        else{
            break;
        }
    }

    for(int j = 1;j < i;j++){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString("save%1").arg(j));
        item->setTextAlignment(Qt::AlignCenter);
        item->setSizeHint(QSize(60,50));
        listWidget->addItem(item);
        m[item->text()] = j;
    }
}

void savedialog::choose(QListWidgetItem *item){
    QMessageBox *msgbox = new QMessageBox();
    msgbox->setText("           请选择操作");
    msgbox->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgbox->button(QMessageBox::No)->setText("读取存档");
    msgbox->button(QMessageBox::Yes)->setText("删除存档");
    int result=msgbox->exec();
    if(result == QMessageBox::No){
        int n = m[item->text()];
        emit OK(n);
    }
    else{
        int n = m[item->text()];
        QString path1 = QDir::currentPath();
        QString path2 = QString("/save%1.txt").arg(n);
        QString fullpath = path1 + path2;
        QFileInfo fileInfo(fullpath);
        if(fileInfo.isFile()){
            QFile::remove(fullpath);
        }
    }
    this->close();
}
