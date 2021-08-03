#ifndef MEASSAGE_H
#define MEASSAGE_H

#include <QtGlobal>

class meassage
{
public:
    meassage();

public:
    enum msgType {MSG_TYPE_CAN, MSG_TYPE_LIN };
    enum dirType {DIR_RX, DIR_TX };

public:
    quint32 Id;
    quint8  length;
    quint8  data[8];
    quint32 timeStamp;
    dirType dir;
};

#endif // MEASSAGE_H
