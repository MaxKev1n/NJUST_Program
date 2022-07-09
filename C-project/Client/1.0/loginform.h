#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTcpSocket>

class loginform : public QDialog
{
    Q_OBJECT
public:
    explicit loginform(QDialog *parent = 0);
signals:

public slots:
    void login();
private:
    QLabel *username1;
    QLineEdit *username2;
    QLabel *userpassword1;
    QLineEdit *userpassword2;
    QPushButton *loginB;
    QPushButton *esc;
    QTcpSocket *socket1;

};

#endif // LOGINFORM_H
