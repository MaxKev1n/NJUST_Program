#include <choosehead.h>

 choosehead :: choosehead(QDialog *parent) : QDialog(parent)
 {
     this->setWindowTitle(tr("提示"));
     this->setFixedSize(400, 400);

     notice = new QLabel(this);
     notice->move(100, 10);
     notice->resize(200, 40);
     notice->setText(tr("村长被放逐，请移交村长"));

     listwidget = new QListWidget(this);
     listwidget->show();
     listwidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     listwidget->resize(200, 200);
     listwidget->move(50, 150);
     connect(listwidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(choose(QListWidgetItem*)));

 }

 void choosehead::choose(QListWidgetItem *item)
 {
     int num = map[item->text()];
     QMessageBox *msgbox = new QMessageBox();
     msgbox->setText(QString("%1号玩家已成为村长").arg(num + 1));
     msgbox->setStandardButtons(QMessageBox::Yes);
     msgbox->button(QMessageBox::Yes)->setText("确定");
     int result=msgbox->exec();
     if(result == QMessageBox::Yes){
         emit headnum(num);
     }

 }
