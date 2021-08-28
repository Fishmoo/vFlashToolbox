#ifndef COMM_H
#define COMM_H

#include <QThread>
#include <QObject>
#include "Tp/tp.h"
#include "Com.h"
#include "../SDK/simulator.h"

#define COMM_THREAD_IN_HEAP                 (0)
#define COMM_THREAD_IN_STACK                (1)
#define COMM_THREAD_CREATE_POS              COMM_THREAD_IN_STACK

/**
 * @brief The ComM class
 * Communication Manager, it used to:
 * - Initialize the hardware communication simulator;
 * - Crate the thread for the communication;
 */
class ComM : public QObject
{
    Q_OBJECT
public:
    enum ComMode {NO_COM, FULL_COM};

public:
    ComM(QObject *parent = nullptr);
    ~ComM();

public slots:
    /* 接收UI控制信号.*/
    void on_ComControl(const bool isActiveCom);
//    void on_startFlashing();

//    void on_SimuConfig();
    void on_SimuControl(const bool isStart);

    /* 接收硬件状态信号.*/
//    void on_isOpenSimuOk(const bool isSuccess);
//    void on_isCloseSimuOk(const bool isSuccess);

signals:
    /* 将接收UI控制信号发射给Com控制通讯用.*/
    void startCom();
    void stopCom();

    void openSimulator();
    void closeSimulator();
public:
    simulator   *m_pSimulator;

private:
    ComMode     m_ComRequested;
    ComMode     m_ComMode;
    bool        m_isComActive;


    Com         *m_pComWorker;
    QThread     m_ComThread;
//    QThread     m_SimThread;

    void createComThread();
    void destroyComThread();
};

#endif // COMM_H
