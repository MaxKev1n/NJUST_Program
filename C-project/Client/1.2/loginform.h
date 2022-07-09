#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <headers.h>

class loginform : public QDialog
{
    Q_OBJECT
    friend class mainform;
public:
    explicit loginform(QDialog *parent = 0);
signals:

public slots:
    void logindb();
    void registerP();
public:
    QLabel *username1;
    QLineEdit *username2;
    QLabel *userpassword1;
    QLineEdit *userpassword2;
    QPushButton *loginB;
    QPushButton *esc;
    QPushButton *reg;
    QTcpSocket *socket1;

};

class addfriend : public QDialog
{
    Q_OBJECT
public:
    explicit addfriend(QDialog *parent = 0);
    QString username;
signals:
    void refresh();
private:
    QPushButton *search;
    QPushButton *add;
    QLineEdit *addname;
public slots:
    void searchuser();
    void adduser();

};


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

public slots:
    void send();
    void receive();
    void friends();
    void communicate(QListWidgetItem *item);
    void addfriends();
};

class regist : public QDialog
{
    Q_OBJECT
public:

    explicit regist(QDialog *parent = 0);

    QLabel *username1;
    QLineEdit *username2;
    QLabel *userpassword1;
    QLineEdit *userpassword2;
    QPushButton *registP;

public slots:
    void registdb();
};


#endif // LOGINFORM_H
