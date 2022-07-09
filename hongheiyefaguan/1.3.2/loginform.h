#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <headers.h>
#include <player.h>
#include <choosehead.h>


class mainform : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainform(QWidget *parent = 0);
    int number = 0;
    QVector<player> p;
    QVector<player> temp;
    int tempnumber = number;
    choosehead *ch;
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
    QPushButton *openeyes;
    QPushButton *notopeneyes;
    QLabel *playername;
    bool boolnight = false;  //红true，黑false
    int index = 1;
    int count = 1;
    int day = 0;
    bool isnight = true;
    QMap<QString, int> map;
    int opennumber = 0;
    int n = 1;
    int headnumber = number;
    bool rol = false; //tr,fl
    int countred = 0;
    int countblack = 0;
    bool finish = false;
    bool labelisempty = false;

    ~mainform(){
        delete ch;
    }

public slots:
    void change();
    void send();
    void zhengyan();
    void notzhengyan();
    void tp1(QListWidgetItem*);
    void changehead(int);
public:
    void toupiao(QListWidget*, QVector<player>);
    void judge(QVector<player>);
    void headchange(int);

};


#endif // LOGINFORM_H
