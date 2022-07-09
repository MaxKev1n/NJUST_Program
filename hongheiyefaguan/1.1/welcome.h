#ifndef WELCOME_H
#define WELCOME_H

#include <headers.h>

class welcome : public QDialog
{
    Q_OBJECT
public:
    explicit welcome(QDialog *parent = 0);
    QLabel *number;
    QLineEdit *inputnum;
    QPushButton *start;
public slots:
    void startgame();
};
#endif // WELCOME_H
