#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trace.h"
#include <QTimer>
#include "./SDK/simulator.h"
#include "ComStack/ComM.h"
#include <QThread>
#include "fileAddition.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void ComControl(bool isActiveCom);

private slots:
    void on_pushButton_flash();
    void on_toolButton_simuCtrl();

private:
    Ui::MainWindow *ui;

    trace   *traceWidget;
    QThread *mTraceThread;
    QTimer* tickTimer;
    bool    isRunning;

    ComM    *pComM;
    bool    isComActived;
};
#endif // MAINWINDOW_H
