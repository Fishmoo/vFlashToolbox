#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QLibrary>
#include <QObject>
#include "ComStack/Common/Std_Types.h"
#include "ComStack/Common/ComStack_Types.h"
#include <QThread>
#include "msg.h"
#include <QQueue>

/**
 * @brief lldStatus
 * -1: simulator disconnect from USB.
 * -2: load dynamic library failed.
 */
typedef short   lldStatus;
#define LLD_E_OK                (0)
#define LLD_E_NOT_OK            (-1)

/**
 * @brief The simulator class is a abstract of the
 * hardware simulator device.
 */
class simulator : public QThread
{
    Q_OBJECT
public:
    simulator(const QString &dllName);
    virtual ~simulator();

public:
    typedef enum {SIMU_CMD_STOP, SIMU_CMD_START} enSimuCmdType;
    typedef enum {SIMU_OFFLINE, SIMU_ONLINE } enSimuOpStsType;
    typedef enum {CAN_125K, CAN_250K, CAN_500K} CanBaudrate_t;

public:
    /**
     * @brief loadDriver
     * this interface is used to load dirver from the dll file, and
     * it shall be called in the constructor.
     * e.g. load dymatic library.
     */
    virtual lldStatus   loadDriver()   = 0;

    /**
     * @brief unloadDriver
     * this interface is used to unload dirver of the simulator, and
     * it shall be called in the destructor.
     * e.g. unload dymatic library.
     */
    virtual lldStatus   unloadDriver() = 0;

    /* ---------------- Simulator control -----------------------.*/
    /**
     * @brief connect/disconect
     * these two interfaces are used to connect/disconnect the device.
     * e.g. open/close the device.
     */
    virtual lldStatus   connect()      = 0;
    virtual void        disconnect()   = 0;

    /**
     * @brief isOnline
     * Check if the device is opened successfully.
     * @return
     * - false: falied;
     * - true : success;
     */
    virtual bool        isOnline() const;
    virtual lldStatus   readSimDeviceInfo();

    virtual void        doComTask()   = 0;

    /* CAN.*/
    virtual lldStatus   CAN_Init() = 0;
    virtual lldStatus   CAN_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) = 0;
    virtual lldStatus   CAN_Receive() = 0;
    virtual void        setCanBaudrate(const CanBaudrate_t speed, void* param2Set) = 0;

    /**
     * @brief RxConvertion
     * It used to convert the Hardware Reacive Handle to the message frame,
     * and emit it through the signal RxIndication.
     * @param Hth: Hardware Reacive Handle that include message.
     * @param size: Hrh size.
     */
    virtual void        RxConvertion(void *Hrh, int size) = 0;

    /**
     * @brief TxConvertion
     * It used to convert the Hardware Transmit Handle to the message frame,
     * and emit it through the signal TxConfirmation.
     * @param Hth: Hardware Transmit Handle that include message.
     * @param size: Hth size.
     */
    virtual void        TxConvertion(void *Hth, int size) = 0;

signals:
    void loadDriverStatus(const bool isSuccess);
    void unloadDriverStatus(const bool isSuccess);
    void openSimuStatus(const bool isSuccess);
    void RxIndication(QQueue<meassage> *pMsgQue);
    void TxConfirmation(QQueue<meassage> *pMsgQue);

public slots:


protected:
    QLibrary*           m_pSimDll;
    bool                m_isLoadDllSuccess;
    bool                m_isOnline;

    QQueue<meassage>    *m_pMsgRxQueue;
    QQueue<meassage>    *m_pMsgTxQueue;
public:
    enSimuCmdType       m_cmdRequested;
    enSimuOpStsType     m_simuOpState;
};

#endif // SIMULATOR_H
