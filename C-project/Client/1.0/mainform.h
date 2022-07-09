#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QLabel>

class mainform : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainform(QWidget *parent = 0);
private:
    QLabel *welcome;
};

#endif // MAINFORM_H
