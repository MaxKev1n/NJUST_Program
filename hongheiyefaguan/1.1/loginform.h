#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <headers.h>



class mainform : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainform(QWidget *parent = 0);
    int number;


private:
    QTextEdit *input;
    QTextBrowser *displaytext;
    QPushButton *sendp;
    QPushButton *next;
    QLabel *night;
    QString nightcolor;
    QListWidget *listWidget;
    QLabel *image;

};


#endif // LOGINFORM_H
