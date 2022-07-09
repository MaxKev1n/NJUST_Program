#ifndef WELCOME_H
#define WELCOME_H

#include <headers.h>
#include <loginform.h>
#include <savedialog.h>
#include <player.h>

class welcome : public QDialog
{
    Q_OBJECT
public:
    explicit welcome(QDialog *parent = 0);
    mainform *main;
    savedialog *dialog;

    QLabel *number;
    QLineEdit *inputnum;
    QPushButton *start;
    QPushButton *ReadGame;

    void start2(Save, QVector<player>, QVector<player>);

public slots:
    void startgame();
    void Read(int);

signals:
    void startgamesignal();
protected:
    void paintEvent(QPaintEvent *);
};
#endif // WELCOME_H
