#ifndef ZLCAN_H
#define ZLCAN_H

#include "simulator.h"
#include <QLibrary>
#include "ControlCAN.h"
#include <QVector>
#include <QQueue>

/**
 * USBCAN-2A/C
 * CANalyst-II
 */
#define ZL_VCI_USBCAN2              (4)

/**
 * @brief The zlCAN class is used to realize the ZLG CAN board.
 */
class zlCAN : public simulator
{
public:
    zlCAN();
    virtual ~zlCAN();

public:
    lldStatus   loadDriver() override;
    lldStatus   unloadDriver() override;

    void        doComTask() override;

    /* Simulator control.*/
    lldStatus   connect() override;
    void        disconnect() override;
    lldStatus   readSimDeviceInfo() override;

    /* CAN.*/
    lldStatus   CAN_Init() override;
    lldStatus   CAN_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) override;
    lldStatus   CAN_Receive() override;
    void        setCanBaudrate(const CanBaudrate_t speed, void* param2Set) override;
    void        RxConvertion(void *Hrh, int size) override;
    void        TxConvertion(void *Hth, int size) override;

public:
    void run() override;

private:
    pVCI_OpenDevice     pOpenDev        = nullptr;
    pVCI_CloseDevice    pCloseDev       = nullptr;
    pVCI_InitCAN        pInitCAN        = nullptr;
    pVCI_ReadBoardInfo  pReadDevInfo    = nullptr;
    pVCI_SetReference   pSetRef         = nullptr;
    pVCI_GetReceiveNum  pGetRxNum       = nullptr;
    pVCI_ClearBuffer    pClrBuffer      = nullptr;
    pVCI_StartCAN       pStartCAN       = nullptr;
    pVCI_ResetCAN       pResetCAN       = nullptr;
    pVCI_Transmit       pTransmit       = nullptr;
    pVCI_Receive        pReceive        = nullptr;
    pVCI_UsbDeviceReset pUsbDevReset    = nullptr;
    pVCI_FindUsbDevice2 pSearchUsbDev   = nullptr;

    int                 mDevType;
    int                 mDevIdx;
    int                 mCanIdx;
    VCI_BOARD_INFO      mDeviceInfo;
    VCI_INIT_CONFIG     mDeviceInitCfg;
    VCI_CAN_OBJ         mHth2Txd;
    VCI_CAN_OBJ         mHrh4Rxd[1000];
    QQueue<VCI_CAN_OBJ> *pTxMailbox;
    QQueue<VCI_CAN_OBJ> *pRxMailbox;
};

#endif // ZLCAN_H
