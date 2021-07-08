#ifndef COM_H
#define COM_H

#include <QObject>
#include <QThread>
#include "Tp/tp.h"
#include "../SDK/simulator.h"
#include "../SDK/zlCAN.h"

class Com : public QObject
{
    Q_OBJECT
public:
    explicit    Com(QObject *parent = nullptr);
    void        stopCom();

signals:

public slots:
    void        on_doMainTask();

private:
    bool        m_isComActive;
    Tp          *m_pCanTp;
//    simulator   *m_pSimulator;
    void        on_startCom();
};

#endif // COM_H
