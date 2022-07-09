#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <headers.h>

class savedialog : public QDialog
{
    Q_OBJECT
public:
    explicit savedialog(QDialog *parent = 0);
    QListWidget *listWidget;
    QMap<QString, int> m;
    void begin();

public slots:
    void choose(QListWidgetItem*);
signals:
    void OK(int);
};

#endif // SAVEDIALOG_H
