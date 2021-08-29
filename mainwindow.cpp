#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QIcon>
#include <QPixmap>
#include "./SDK/zlCAN.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , uiFileAdd(new fileAddition)
    , isRunning(false)
    , isComActived(false)
{
    ui->setupUi(this);

    this->traceWidget = new trace();
    ui->gridLayout_trace->addWidget(this->traceWidget);
    ui->gridLayout4fileAdd->addWidget(uiFileAdd);

    this->tickTimer = new QTimer;
//    connect(this->tickTimer, SIGNAL(timeout()), this->traceWidget, SLOT(on_RxTxMessage()));
    connect(this->ui->pushBtn_Flash, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_flash()));
    connect(this->ui->toolBtn_ComCtrl, &QToolButton::clicked,
            this, &MainWindow::on_toolButton_simuCtrl);

    //Commnunication
    this->pComM = new ComM();
    connect(this, &MainWindow::ComControl,
            this->pComM, &ComM::on_ComControl);
#if (1) //todo: for test trace tabel widget
    void (trace::*on_RxTxMessage)() = &trace::on_RxTxMessage;
#else
    void (trace::*on_RxTxMessage)(QQueue<meassage> *pMsgQue) = &trace::on_RxTxMessage;
#endif
    connect(pComM->m_pSimulator, &zlCAN::RxIndication,
                this->traceWidget, on_RxTxMessage);
    connect(pComM->m_pSimulator, &zlCAN::TxConfirmation,
                this->traceWidget, on_RxTxMessage);

#if (0) //todo: 刷新线程暂定!!!
    mTraceThread = new QThread(nullptr);
    this->traceWidget->moveToThread(mTraceThread);
    connect(mTraceThread, &QThread::finished, this->traceWidget, &trace::deleteLater);
    /* 如果工作线程分配到堆上, 自杀QThread线程用.*/
    connect(mTraceThread, &QThread::finished, mTraceThread, &QObject::deleteLater);
    /* 启动刷新线程.*/
    mTraceThread->start();
#endif
}

MainWindow::~MainWindow()
{
#if (0) //todo: 刷新线程暂定!!!
    if (!mTraceThread->isFinished()) {
        qDebug("On MainWindow - Destroy the Com thread!!!");
        /* 停止线程并等待线程释放完毕.*/
        mTraceThread->quit();
        mTraceThread->wait();
    }
#endif
    delete ui;
    delete uiFileAdd;
}

/****************[public members - slots]***************************************************************/
void MainWindow::on_pushButton_flash()
{
    if (!isRunning) {
        isRunning = true;
        this->tickTimer->setInterval(1000);
        this->tickTimer->start();
    } else {
        isRunning = false;
        this->tickTimer->stop();
    }
    qDebug("on event flashing!");
}

void MainWindow::on_toolButton_simuCtrl()
{
    qDebug("MainWindow::on_toolButton_simuCtrl!!!");
    QIcon toolBtnIcon;
    if (isComActived) {
        isComActived = false;
        toolBtnIcon.addPixmap(QPixmap(":/icon/Resources/icon/connect.png"));
    } else {
        isComActived = true;
        toolBtnIcon.addPixmap(QPixmap(":/icon/Resources/icon/disconnect.png"));
    }
    this->ui->toolBtn_ComCtrl->setIcon(toolBtnIcon);
    emit ComControl(isComActived);
}




