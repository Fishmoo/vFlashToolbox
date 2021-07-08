#include "ComM.h"
#include <QDebug>

ComM::ComM(QObject *parent) :
    QObject(parent),
    m_isComActive(false),
    m_pComWorker(nullptr)
{
    m_ComRequested = NO_COM;
    m_ComMode      = NO_COM;

    m_pSimulator   = new zlCAN();
}

ComM::~ComM()
{
    delete m_pSimulator;

#if (COMM_THREAD_CREATE_POS == COMM_THREAD_IN_STACK)
    destroyComThread();
#endif
}


/**
 * @brief ComM::on_ComControl
 * 接收UI控制信号, 控制硬件以及通信协议;
 * @param isActiveCom
 */
void ComM::on_ComControl(bool isActiveCom)
{
    if (isActiveCom) {
        qDebug("ComM::on_ComControl - Active!!!");
        if (m_pSimulator->connect() == LLD_E_OK) {
            createComThread();
            emit startCom();
            m_isComActive = true;
        } else {
            // todo: 弹窗
        }
    } else {
        qDebug("ComM::on_ComControl - Deactive!!!");
        if ((m_pComWorker) && (m_isComActive)) {
            m_pComWorker->stopCom();
#if (COMM_THREAD_CREATE_POS == COMM_THREAD_IN_HEAP)
            destroyComThread();
#endif
            (void)m_pSimulator->disconnect();
            m_isComActive = false;
        }
    }
}

void ComM::on_SimuControl(const bool isStart)
{
    if (isStart) {
        emit openSimulator();
    } else {
        emit closeSimulator();
    }
}


/**
 * @brief ComM::createComThread
 * 创建线程.
 */
void ComM::createComThread()
{
    if (!m_pComWorker) {
        /* 创建Com,并转移到新线程.*/
        m_pComWorker = new Com(nullptr);
        m_pComWorker->moveToThread(&m_ComThread);
        connect(&m_ComThread, &QThread::finished, m_pComWorker, &Com::deleteLater);
        /* 如果工作线程分配到堆上,自杀QThread线程用.*/
#if (COMM_THREAD_CREATE_POS == COMM_THREAD_IN_HEAP)
        connect(m_pComThread, &QThread::finished, m_pComThread, &QObject::deleteLater);
#endif
        connect(this, &ComM::startCom, m_pComWorker, &Com::on_doMainTask);

        /* 启动线程.*/
        m_ComThread.start();
    }
}

/**
 * @brief ComM::destroyComThread
 * 销毁线程, 根据创建位置有两种情况:
 * 1)如果线程在栈上(QThread  thread), 由操作系统销毁;
 * 2)如果线程在堆上(QThread *thread), 没有父对象的指针要想正常销毁, 需要将线程的finished()信号关联到
 *   QObject 的 deleteLater() 让其在正确的时机被销毁;
 */
void ComM::destroyComThread()
{
    if (!m_ComThread.isFinished()) {
        qDebug("Destroy the Com thread!!!");
        /* 停止线程并等待线程释放完毕.*/
        m_ComThread.quit();
        m_ComThread.wait();
    }
}


