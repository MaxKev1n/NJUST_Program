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
    bool friendonline;

public slots:
    void send();
    void receive();
    void friends();
    void communicate(QListWidgetItem *item);
    void addfriends();
};

struct messages{
    char *sender;
    char *receiver;
    char *msg;
};
#endif // MAINFORM_H
