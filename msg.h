#ifndef MEASSAGE_H
#define MEASSAGE_H

#include <QtGlobal>

class meassage
{
public:
    meassage();

public:
    enum msgType {MSG_TYPE_CAN, MSG_TYPE_LIN };

public:
    quint32 CanId;
    quint8  length;
    quint8  data[8];
};

#endif // MEASSAGE_H
