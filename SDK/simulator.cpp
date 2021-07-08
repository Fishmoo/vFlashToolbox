#include "simulator.h"

#include <QMessageBox>
#include "ControlCAN.h"

simulator::simulator(const QString &dllName) :
    m_cmdRequested(SIMU_CMD_STOP),
    m_simuOpState(SIMU_OFFLINE),
    m_isLoadDllSuccess(false),
    m_isOnline(false)
{
    /* load library.*/
    m_pSimDll = new QLibrary(dllName);
}

simulator::~simulator()
{
    if (m_pSimDll) {
        delete m_pSimDll;
    }
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

