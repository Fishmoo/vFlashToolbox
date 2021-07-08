#include "zlCAN.h"
#include "ControlCAN.h"
#include <QMessageBox>


zlCAN::zlCAN(): simulator("./lib/ControlCAN")
{
    /* Open library.*/
    m_isLoadDllSuccess = (loadDriver() == LLD_E_OK) ?
                true : false;
    emit loadDriverStatus(m_isLoadDllSuccess);
    if (m_isLoadDllSuccess) {
        pReadDevInfo(4, 0, &mDeviceInfo);
    }

    mDeviceInitCfg.Mode = 1;
    mDeviceInitCfg.Filter = 0;

    pTxMailbox  = new QQueue<VCI_CAN_OBJ>(48);
}

zlCAN::~zlCAN()
{
    (void)unloadDriver();

    delete pTxMailbox;
}


lldStatus zlCAN::loadDriver()
{
    /* Load the dll driver into the memory.*/
    if (!m_pSimDll->load()) {
        qDebug("The dynamic library of ControlCAN loads failed!");
        return LLD_E_NOT_OK;
    }

    quint32 NotFound = 0u;
    if ((pOpenDev        = (pVCI_OpenDevice)    m_pSimDll->resolve("VCI_OpenDevice"))     == nullptr)     NotFound = 1U;
    if ((pCloseDev       = (pVCI_CloseDevice)   m_pSimDll->resolve("VCI_CloseDevice"))    == nullptr)     NotFound = 2U;
    if ((pInitCAN        = (pVCI_InitCAN)       m_pSimDll->resolve("VCI_InitCAN"))        == nullptr)     NotFound = 3U;
    if ((pReadDevInfo    = (pVCI_ReadBoardInfo) m_pSimDll->resolve("VCI_ReadBoardInfo"))  == nullptr)     NotFound = 4U;
    if ((pSetRef         = (pVCI_SetReference)  m_pSimDll->resolve("VCI_SetReference"))   == nullptr)     NotFound = 5U;
    if ((pGetRxNum       = (pVCI_GetReceiveNum) m_pSimDll->resolve("VCI_GetReceiveNum"))  == nullptr)     NotFound = 6U;
    if ((pClrBuffer      = (pVCI_ClearBuffer)   m_pSimDll->resolve("VCI_ClearBuffer"))    == nullptr)     NotFound = 7U;
    if ((pStartCAN       = (pVCI_StartCAN)      m_pSimDll->resolve("VCI_StartCAN"))       == nullptr)     NotFound = 8U;
    if ((pResetCAN       = (pVCI_ResetCAN)      m_pSimDll->resolve("VCI_ResetCAN"))       == nullptr)     NotFound = 9U;
    if ((pTransmit       = (pVCI_Transmit)      m_pSimDll->resolve("VCI_Transmit"))       == nullptr)     NotFound = 10U;
    if ((pReceive        = (pVCI_Receive)       m_pSimDll->resolve("VCI_Receive"))        == nullptr)     NotFound = 11U;
    if ((pUsbDevReset    = (pVCI_UsbDeviceReset)m_pSimDll->resolve("VCI_UsbDeviceReset")) == nullptr)     NotFound = 12U;
    if ((pSearchUsbDev   = (pVCI_FindUsbDevice2)m_pSimDll->resolve("VCI_FindUsbDevice2")) == nullptr)     NotFound = 13U;

    if (NotFound) {
        qDebug("dll symbol resolve faild.");
        return LLD_E_NOT_OK;
    } else {
        qDebug("All dll symbols resolve successfully.");
        return LLD_E_OK;
    }
}

lldStatus zlCAN::unloadDriver()
{
    /* unload library happens automatically on application termination.*/
    return (!m_pSimDll->unload()) ? LLD_E_NOT_OK : LLD_E_OK;
}

lldStatus zlCAN::connect()
{
    m_cmdRequested = SIMU_CMD_START;

    if (!m_isLoadDllSuccess) {
        QMessageBox::information(NULL, "NO", "DLL loaded failed!");
        return LLD_E_NOT_OK;
    }

    /* a.Open the device.*/
    if (pOpenDev(4, 0, 0) != 1) {
        QMessageBox::information(NULL, "NO", "Open device failed!");
        return LLD_E_NOT_OK;
    }

    /* b.Init the relevent channel of the device.*/
    setCanBaudrate(CAN_500K, (void*)&mDeviceInitCfg);
    pInitCAN(4, 0, 0, &mDeviceInitCfg);
    m_isOnline = true;
    return LLD_E_OK;
}

void zlCAN::disconnect()
{
    m_cmdRequested = SIMU_CMD_STOP;
    m_simuOpState = SIMU_OFFLINE;

    if (m_isLoadDllSuccess && m_isOnline) {
        (void)pCloseDev(4, 0);
    }
    m_isOnline = false;
}

lldStatus zlCAN::readSimDeviceInfo()
{
    return LLD_E_OK;
}

lldStatus zlCAN::CAN_Init()
{

    return LLD_E_OK;
}

lldStatus zlCAN::CAN_Transmit()
{
//    if (!pTxMailbox->isEmpty()) {
//        pTransmit(4, 0, 0, (pTxMailbox->dequeue()), 1);
//    }

    return LLD_E_OK;
}

lldStatus zlCAN::CAN_Receive()
{
    return LLD_E_OK;
}

void zlCAN::setCanBaudrate(const CanBaudrate_t speed, void* param2Set)
{
    VCI_INIT_CONFIG *InitCfg = (VCI_INIT_CONFIG*)(param2Set);
    switch (speed) {
    case CAN_125K:
        InitCfg->Timing0 = 0x03;
        InitCfg->Timing1 = 0x1C;
        break;
    case CAN_250K:
        InitCfg->Timing0 = 0x01;
        InitCfg->Timing1 = 0x1C;
        break;
    case CAN_500K:
        InitCfg->Timing0 = 0x00;
        InitCfg->Timing1 = 0x1C;
        break;
    default:
        break;
    }
}
