#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <headers.h>
#include <player.h>
#include <choosehead.h>
#include <save.h>

class mainform : public QMainWindow
{
    Q_OBJECT
public:
    Save gamesave;
    explicit mainform(QWidget *parent = 0);
    int number = 0;
    QVector<player> p;
    QVector<player> temp;
    int TotalNumber = number;
    choosehead *ch;
    void start();
    void start2();

    friend class welcome;


private:
    QTextEdit *input;
    QTextBrowser *displaytext;
    QPushButton *sendp;
    QPushButton *next;
    QLabel *night;
    QListWidget *listWidget;
    QLabel *image;
    QPushButton *openeyes;
    QPushButton *notopeneyes;
    QLabel *playername;
    QPushButton *savegame;
    bool boolnight = false;  //红true，黑false
    int index = 0;
    int day = 0;
    bool isnight = true;
    int nightcolor;
    QMap<QString, int> map;
    int opennumber = 0;
    int n = 0;
    int headnumber = number;
    bool rol = false; //tr,fl
    int countred = 0;
    int countblack = 0;
    bool finish = false;
    int stage; //2 == toupiao, 3 == zhengyan, 4 == fayan,

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
    void SaveGame();
public:
    void toupiao(QListWidget*);
    void judge(QVector<player>);
    void headchange(int);

};


#endif // LOGINFORM_H
