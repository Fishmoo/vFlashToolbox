#include "zlCAN.h"
#include "ControlCAN.h"
#include <QMessageBox>
#include <QDebug>

zlCAN::zlCAN(): simulator("./lib/ControlCAN"),
    mDevType(ZL_VCI_USBCAN2),
    mDevIdx(0),
    mCanIdx(0)
{
    /* Open library.*/
    m_isLoadDllSuccess = (loadDriver() == LLD_E_OK) ?
                true : false;
    emit loadDriverStatus(m_isLoadDllSuccess);
    if (m_isLoadDllSuccess) {
        pReadDevInfo(4, 0, &mDeviceInfo);
    }

    mHth2Txd.SendType   = 1;    /* 单次发送(只发送一次,不自动重发).*/
    mHth2Txd.RemoteFlag = 0;    /* =0时为数据帧,=1时为远程帧.*/
    mHth2Txd.ExternFlag = 0;    /* =0时为标准帧(11位ID), =1时为扩展帧(29位ID).*/
    //todo:
    mHth2Txd.ID = 0x715;
    mHth2Txd.DataLen = 4;
    mHth2Txd.Data[0] = 0x11;
    mHth2Txd.Data[2] = 0x22;
    mHth2Txd.Data[3] = 0x33;
    mHth2Txd.Data[4] = 0x44;


    pTxMailbox = new QQueue<VCI_CAN_OBJ>;

    //todo:
}

zlCAN::~zlCAN()
{
    disconnect();
    (void)unloadDriver();

    delete pTxMailbox;
}

/**
 * @brief zlCAN::loadDriver
 * @return
 */
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

/**
 * @brief zlCAN::unloadDriver
 * @return
 */
lldStatus zlCAN::unloadDriver()
{
    /* unload library happens automatically on application termination.*/
    return (!m_pSimDll->unload()) ? LLD_E_NOT_OK : LLD_E_OK;
}

/**
 * @brief zlCAN::connect
 * @return
 */
lldStatus zlCAN::connect()
{
    lldStatus opResult = LLD_E_NOT_OK;
    m_cmdRequested = SIMU_CMD_START;
    bool isOpenCalled = false;

    do {
        /* a.Check if the .dll is loaded successfully.*/
        if (!m_isLoadDllSuccess) {
            QMessageBox::information(NULL, "NO", ".DLL loaded failed!");
            break;
        }

        /* b.Open the device.*/
        isOpenCalled = true;
        if (pOpenDev(mDevType, mDevIdx, 0) != 1) {
            QMessageBox::information(NULL, "NO", "Open device failed!");
            break;
        }

        (void)pClrBuffer(mDevType, mDevIdx, 0);

        /* c.Init the relevent channel of the device.*/
        mDeviceInitCfg.Mode   = 0u;
        mDeviceInitCfg.Filter = 1u;
        mDeviceInitCfg.AccCode = 0x80000000u;
        mDeviceInitCfg.AccMask = 0xFFFFFFFFu;
        setCanBaudrate(CAN_500K, (void*)&mDeviceInitCfg);
        if (pInitCAN(mDevType, mDevIdx, 0, &mDeviceInitCfg) != 1) {
            QMessageBox::information(NULL, "NO", "Init device failed!");
            break;
        }

        /* d.Start CAN, current only support one channel.*/
        if (pStartCAN(mDevType, mDevIdx, 0) != 1) {
            QMessageBox::information(NULL, "NO", "Start CAN channel failed!");
            break;
        }

        m_isOnline = true;  /* the device is opened.*/
        opResult = LLD_E_OK;
    } while (0);

    if ((isOpenCalled) && (opResult != LLD_E_OK)) {
        pCloseDev(mDevType, mDevIdx);
    }

    return opResult;
}

/**
 * @brief zlCAN::disconnect
 */
void zlCAN::disconnect()
{
    m_cmdRequested = SIMU_CMD_STOP;
    m_simuOpState = SIMU_OFFLINE;

    /* Clear the FIFO.*/
    m_pMsgRxQueue->clear();
    m_pMsgTxQueue->clear();

    if (m_isOnline) {
        (void)pCloseDev(mDevType, mDevIdx);
    }
    m_isOnline = false;
}

lldStatus zlCAN::readSimDeviceInfo()
{
    return LLD_E_OK;
}

void zlCAN::doComTask()
{
    VCI_CAN_OBJ hth;
    PduInfoType pdu;
    uint8 sdu[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    pdu.SduLength = 8U;
    pdu.SduDataPtr = sdu;
    while (m_isOnline) {
        CAN_Transmit(0x715, &pdu);
        if (!pTxMailbox->isEmpty()) {
            hth = pTxMailbox->dequeue();
            pTransmit(4, 0, 0, &hth, 1);
        }
        sleep(1);
    }
}

void zlCAN::run()
{
    // doComTask
    uint16 canId = 0x111;
    VCI_CAN_OBJ hth;
    PduInfoType pdu;
    uint8 sdu[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    pdu.SduLength = 8U;
    pdu.SduDataPtr = sdu;

    while (m_isOnline) {
        CAN_Transmit(canId, &pdu);
        if (!pTxMailbox->isEmpty()) {
            hth = pTxMailbox->dequeue();
            (void)pTransmit(mDevType, mDevIdx, 0, &hth, 1);
            TxConvertion(static_cast<void *>(&hth), 1);
        }

        const int frameRxd = pReceive(mDevType, mDevIdx, 0, mHrh4Rxd, 1000, 0);
        if (frameRxd > 0) {
            RxConvertion(static_cast<void *>(mHrh4Rxd), frameRxd);
        }
        /* 调用频率: 调用VCI_Receive函数,实质是读写USB,读写USB有一个最小的耗时,一般
        为3～5ms,故VCI_Receive函数调用间隔至少应设置在5ms以上.*/
        msleep(6);
    }
}

void zlCAN::RxConvertion(void *Hrh, int size)
{
    VCI_CAN_OBJ *pRxObj = (VCI_CAN_OBJ *)Hrh;
    meassage msg;
    m_pMsgRxQueue->clear();
    for (int i = 0; i < size; ++i,++pRxObj) {
        if (pRxObj->TimeFlag != 1) {
            continue;
        }
        msg.Id        = pRxObj->ID;
        msg.length    = pRxObj->DataLen;
        msg.timeStamp = pRxObj->TimeStamp;
        msg.dir       = meassage::DIR_RX;
        memcpy(msg.data, pRxObj->Data, pRxObj->DataLen);
        m_pMsgRxQueue->enqueue(msg);
        qDebug() << QString("%2").arg(msg.Id,3,16) << QString(" - %2").arg(msg.timeStamp,10,10);
    }
    if (!m_pMsgRxQueue->isEmpty()) {
        emit RxIndication(m_pMsgRxQueue);
    }
}

void zlCAN::TxConvertion(void *Hth, int size)
{
    VCI_CAN_OBJ *pRxObj = (VCI_CAN_OBJ *)Hth;
    meassage msg;
    m_pMsgTxQueue->clear();
    for (int i = 0; i < size; ++i,++pRxObj) {
        msg.Id        = pRxObj->ID;
        msg.length    = pRxObj->DataLen;
        msg.timeStamp = pRxObj->TimeStamp;
        msg.dir       = meassage::DIR_TX;
        memcpy(msg.data, pRxObj->Data, pRxObj->DataLen);
        m_pMsgTxQueue->enqueue(msg);
    }
    if (!m_pMsgTxQueue->isEmpty()) {
        emit TxConfirmation(m_pMsgTxQueue);
    }
}

/****************[public members - interface]***********************************************************/

/****************[public members - slots]***************************************************************/
lldStatus zlCAN::CAN_Init()
{

    return LLD_E_OK;
}

lldStatus zlCAN::CAN_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
    mHth2Txd.ID = TxPduId;
    if (PduInfoPtr->SduLength <= 8U) {
        mHth2Txd.DataLen = PduInfoPtr->SduLength;
        for (uint8 i = 0U; i < mHth2Txd.DataLen; ++i) {
            mHth2Txd.Data[i] = PduInfoPtr->SduDataPtr[i];
        }
        pTxMailbox->enqueue(mHth2Txd);
    }

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
        InitCfg->Timing0 = 0x03u;
        InitCfg->Timing1 = 0x1Cu;
        break;
    case CAN_250K:
        InitCfg->Timing0 = 0x01u;
        InitCfg->Timing1 = 0x1Cu;
        break;
    case CAN_500K:
        InitCfg->Timing0 = 0x00u;
        InitCfg->Timing1 = 0x1Cu;
        break;
    default:
        break;
    }
}
