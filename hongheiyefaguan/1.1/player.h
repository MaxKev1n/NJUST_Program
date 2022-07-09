#ifndef PLAYER_H
#define PLAYER_H

#include <headers.h>

class player{
private:
    QString identity;   //身份
    int number;         //n号玩家
    bool head = false;          //是否为村长,默认为否
    int ballot;         //票数
}
#endif // PLAYER_H
