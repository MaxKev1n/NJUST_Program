#ifndef PLAYER_H
#define PLAYER_H

#include <headers.h>

class player{
public:
    QString identity; //身份
    int identitynum;
    int number;         //n号玩家
    bool head = false;          //是否为村长,默认为否
    double ballot = 0;         //票数
    QImage *img;        //图片
    bool life = true;
};

inline QDataStream& operator>>(QDataStream &in, player &p)
{
    in>>p.identitynum>>p.number>>p.head>>p.ballot>>p.life;
    return in;
}

inline QDataStream& operator<<(QDataStream &out, player &p)
{
    out<<p.identitynum<<p.number<<p.head<<p.ballot<<p.life;
    return out;
}

#endif // PLAYER_H
