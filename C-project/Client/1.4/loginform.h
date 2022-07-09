#ifndef LOGINFORM_H
#define LOGINFORM_H
#include "headers.h"
#include <regist.h>

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

struct table{
    int id;
    QString sender;
    QString receiver;
    QString time;
    QString msg;
};
#endif // LOGINFORM_H
