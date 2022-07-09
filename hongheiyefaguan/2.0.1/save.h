#ifndef SAVE_H
#define SAVE_H

#include <headers.h>
#include <player.h>
#include <loginform.h>

struct Save{
    int stage;
    int TotalNumber;
    int number;
    bool sendp;
    bool next;
    bool night;
    int nightcolor;
    bool listWidget;
    bool image;
    bool openeyes;
    bool notopeneyes;
    bool playername;
    bool boolnight = false;  //红true，黑false
    int index = 0;
    int day = 0;
    bool isnight = true;
    QMap<QString, int> map;
    int opennumber = 0;
    int n = 0;
    int headnumber;
    bool rol = false; //tr,fl
    int countred = 0;
    int countblack = 0;
    bool finish = false;


public slots:
    void SaveGame();
};

inline QDataStream& operator>>(QDataStream &in, Save &save)
{
    in>>save.stage>>save.TotalNumber>>save.number>>save.sendp>>save.next>>save.night>>save.nightcolor>>save.listWidget>>save.image>>save.openeyes>>save.notopeneyes>>save.playername>>save.boolnight>>save.index>>save.day>>save.isnight>>save.map>>save.opennumber>>save.n>>save.headnumber>>save.rol>>save.countred>>save.countblack>>save.finish;
    return in;
}

inline QDataStream& operator<<(QDataStream &out, Save &save)
{
    out<<save.stage<<save.TotalNumber<<save.number<<save.sendp<<save.next<<save.night<<save.nightcolor<<save.listWidget<<save.image<<save.openeyes<<save.notopeneyes<<save.playername<<save.boolnight<<save.index<<save.day<<save.isnight<<save.map<<save.opennumber<<save.n<<save.headnumber<<save.rol<<save.countred<<save.countblack<<save.finish;
    return out;
}




#endif // SAVE_H
