#ifndef WELCOME_H
#define WELCOME_H

#include <headers.h>
#include <loginform.h>

class welcome : public QDialog
{
    Q_OBJECT
public:
    explicit welcome(QDialog *parent = 0);
    mainform *main;

    QLabel *number;
    QLineEdit *inputnum;
    QPushButton *start;
public slots:
    void startgame();

signals:
    void startgamesignal();
};
#endif // WELCOME_H
