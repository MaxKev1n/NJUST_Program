#ifndef CHOOSEHEAD_H
#define CHOOSEHEAD_H
#include <headers.h>
#include <player.h>

class choosehead : public QDialog
{
    Q_OBJECT
public:
    explicit choosehead(QDialog *parent = 0);
    QVector<player> p;
    QListWidget *listwidget;
    QMap<QString, int> map;

private:
    QLabel *notice;
public slots:
    void choose(QListWidgetItem*);
signals:
    void headnum(int);
};
#endif // CHOOSEHEAD_H
