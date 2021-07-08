#ifndef ZLCAN_H
#define ZLCAN_H

#include "simulator.h"
#include <QLibrary>
#include "ControlCAN.h"
#include <QVector>
#include <QQueue>

/**
 * @brief The zlCAN class is used to realize the ZLG CAN board.
 */
class zlCAN : public simulator
{
public:
    zlCAN();
    virtual ~zlCAN();

public:
    virtual lldStatus   loadDriver();
    virtual lldStatus   unloadDriver();

    /* Simulator control.*/
    virtual lldStatus   connect();
    virtual void        disconnect();
    virtual lldStatus   readSimDeviceInfo();

    /* CAN.*/
    virtual lldStatus   CAN_Init();
    virtual lldStatus   CAN_Transmit();
    virtual lldStatus   CAN_Receive();
    virtual void        setCanBaudrate(const CanBaudrate_t speed, void* param2Set);

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

    VCI_BOARD_INFO      mDeviceInfo;
    VCI_INIT_CONFIG     mDeviceInitCfg;

    QQueue<VCI_CAN_OBJ> *pTxMailbox;
    QVector<VCI_CAN_OBJ> *pRxMailbox;
};

#endif // ZLCAN_H
