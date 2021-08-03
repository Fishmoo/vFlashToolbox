#include "simulator.h"

#include <QMessageBox>
#include "ControlCAN.h"

simulator::simulator(const QString &dllName) :
    m_isLoadDllSuccess(false),
    m_isOnline(false),
    m_cmdRequested(SIMU_CMD_STOP),
    m_simuOpState(SIMU_OFFLINE)
{
    /* load library.*/
    m_pSimDll     = new QLibrary(dllName);

    m_pMsgRxQueue = new QQueue<meassage>;
    m_pMsgTxQueue = new QQueue<meassage>;
}

simulator::~simulator()
{
    if (m_pSimDll) {
        delete m_pSimDll;
    }

    delete m_pMsgRxQueue;
    delete m_pMsgTxQueue;
}

bool simulator::isOnline() const
{
    return m_isOnline;
}

lldStatus simulator::readSimDeviceInfo()
{
    if (m_isOnline) {

        return  0;
    } else {
        return -1;
    }
}

