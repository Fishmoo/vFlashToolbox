#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QLibrary>
#include <QObject>

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
class simulator : public QObject
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

    /* CAN.*/
    virtual lldStatus   CAN_Init() = 0;
    virtual lldStatus   CAN_Transmit() = 0;
    virtual lldStatus   CAN_Receive() = 0;
    virtual void        setCanBaudrate(const CanBaudrate_t speed, void* param2Set) = 0;

signals:
    void loadDriverStatus(const bool isSuccess);
    void unloadDriverStatus(const bool isSuccess);
    void openSimuStatus(const bool isSuccess);

public slots:


protected:
    QLibrary*           m_pSimDll;
    bool                m_isLoadDllSuccess;
    bool                m_isOnline;
public:
    enSimuCmdType       m_cmdRequested;
    enSimuOpStsType     m_simuOpState;
};

#endif // SIMULATOR_H
