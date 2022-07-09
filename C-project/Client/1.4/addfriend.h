#ifndef ADDFRIEND_H
#define ADDFRIEND_H
#include "headers.h"

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
#endif // ADDFRIEND_H
