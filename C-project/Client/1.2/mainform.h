#ifndef MAINFORM_H
#define MAINFORM_H

#include <headers.h>

class mainform : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainform(QWidget *parent = 0);
private:
    QTextEdit *input;
    QTextBrowser *displaytext;
    QPushButton *sendp;
public slots:
    void send();
};

#endif // MAINFORM_H
