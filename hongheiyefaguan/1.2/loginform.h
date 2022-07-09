#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <headers.h>
#include <player.h>



class mainform : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainform(QWidget *parent = 0);
    int number = 0;
    QVector<player> p;
    void start();

private:
    QTextEdit *input;
    QPushButton *startp;
    QTextBrowser *displaytext;
    QPushButton *sendp;
    QPushButton *next;
    QLabel *night;
    QString nightcolor;
    QListWidget *listWidget;
    QLabel *image;
    bool boolnight = false;  //红true，黑false
    int index = 1;
    int count = 1;
    int day = 0;


public slots:
    void change();
    void send();

};


#endif // LOGINFORM_H
