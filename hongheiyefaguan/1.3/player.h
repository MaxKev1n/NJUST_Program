#ifndef PLAYER_H
#define PLAYER_H

#include <headers.h>

class player{
public:
    QString identity;   //身份
    int number;         //n号玩家
    bool head = false;          //是否为村长,默认为否
    int ballot = 0;         //票数
    QImage *img;        //图片
};
#endif // PLAYER_H
