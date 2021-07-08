#ifndef TRACE_H
#define TRACE_H

#include "ui_trace.h"
#include <QWidget>
#include <QFont>
#include <QIcon>

namespace Ui {
class trace;
}

class trace : public QWidget
{
    Q_OBJECT

public:
    explicit trace(QWidget *parent = nullptr);
    ~trace();

public:
    typedef struct
    {
        int         time;
        QString     Dir;
        quint32     Id;
        quint32     Dlc;
        QString     msgData;
    } traceItemType;

public:


private:
    void createItemsARow(int currentRow, traceItemType* p_TraceItem);
    void removeItemsARow(int row);

public slots:
    void on_SaveMessage();
    void on_toolBtn_control();
    void on_toolBtn_scroll();
    void on_ClearMessage();
    void on_RxTxMessage();


private:
    Ui::trace *ui;
    int        totalColumn;
    int        totalRow;
    int        currentRow;
    QFont      contentRowFont;
    QIcon      msgIcon;
};

#endif // TRACE_H
