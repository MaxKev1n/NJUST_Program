#ifndef PLAYER_H
#define PLAYER_H

#include <headers.h>

class player{
public:
    QString identity;   //身份
    int number;         //n号玩家
    bool head = false;          //是否为村长,默认为否
    double ballot = 0;         //票数
    QImage *img;        //图片
    bool life = true;
};
#endif // PLAYER_H
