#ifndef LOGINFORM_H
#define LOGINFORM_H
#include "headers.h"

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
#endif // LOGINFORM_H
