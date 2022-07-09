#ifndef MAINFORM_H
#define MAINFORM_H
#include "headers.h"
#include "addfriend.h"

class mainform : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainform(QWidget *parent = 0);
    QString name;
    addfriend *dialog;
    QSqlDatabase userdatabase = QSqlDatabase::addDatabase("QSQLITE");


private:
    QTextEdit *input;
    QTextBrowser *displaytext;
    QPushButton *sendp;
    QUdpSocket *usocket1;
    QUdpSocket *usocket2;
    QListWidget *listWidget;
    QVBoxLayout *layout;
    QString friendsip;
    QMap<QString, QString> map;
    QLabel *friendsname;
    QPushButton *addfriendP;
    QTcpServer *cws;

public slots:
    void send();
    void receive();
    void friends();
    void communicate(QListWidgetItem *item);
    void addfriends();
};
#endif // MAINFORM_H
