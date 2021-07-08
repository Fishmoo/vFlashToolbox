#include "Com.h"
#include <QDebug>

Com::Com(QObject *parent) : QObject(parent)
{
    m_pCanTp = new Tp(Tp::TP_ADDR_NORMAL);
}


void Com::on_startCom()
{
    m_isComActive = true;
    qDebug("Com::on_startCom!!!");
}

void Com::stopCom()
{
    m_isComActive = false;
    qDebug("Com::on_stopCom!!!");
}

void Com::on_doMainTask()
{
    // Initialize the simulator
    on_startCom();

    uint8 data[20] = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u,
                     11u, 12u, 13u, 14u, 15u, 16u, 17u, 18u, 19u};
    PduInfoType PduInfo;
    PduInfo.SduLength = 20U;
    PduInfo.SduDataPtr = data;
    m_pCanTp->Tp_Transmit(0u, &PduInfo);

    while (m_isComActive)
    {
        m_pCanTp->Tp_MainTask();
        QThread::msleep(10ul);
    }
}
