#ifndef REGIST_H
#define REGIST_H
#include "headers.h"
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
#endif // REGIST_H
