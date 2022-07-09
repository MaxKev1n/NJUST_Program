#ifndef MAINFORM_H
#define MAINFORM_H
#include "headers.h"
#include "addfriend.h"

class mainform : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainform(QWidget *parent = 0);
    void successlogin();
    QString name;
    addfriend *dialog;
    QMenu *m1;
    QAction *exita;
    QAction *chooseimage;
    QPixmap *photo;
    QLabel *image;

private:
    QPlainTextEdit *input;
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
    QTcpSocket *socket1;
    bool friendonline;
    bool iscommunicate = false;
    ~mainform(){
        socket1->disconnectFromHost();
        delete dialog;
        delete this;
    }

public slots:
    void send();
    void receive();
    void friends();
    void communicate(QListWidgetItem *item);
    void addfriends();
    void exit();
    void choosei();

};

struct messages{
    QString sender;
    QString receiver;
    QString msg;
    QString time;
};

inline QDataStream& operator>>(QDataStream &in, messages &p)
{
    in>>p.sender>>p.receiver>>p.msg>>p.time;
    return in;
}

inline QDataStream& operator<<(QDataStream &out, messages &p)
{
    out<<p.sender<<p.receiver<<p.msg<<p.time;
    return out;
}


#endif // MAINFORM_H
