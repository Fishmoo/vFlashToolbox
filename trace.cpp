#include "trace.h"

trace::trace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trace),
    totalRow(0),
    currentRow(0),
    mIsTracing(false)
{
    ui->setupUi(this);

    this->msgIcon.addPixmap(QPixmap(":/msg/Resources/mail.png"));

    mTrace = new QList<meassage>;

    // 设置trace 行表头 & 列数
    QStringList headerText;
    headerText <<"Time" << "Dir" << "ID" << "Len" << "Data";
    ui->tableWidget->setColumnCount(headerText.count());

    QTableWidgetItem *headerItem;
    QSize itemSize;
    for (int i=0; i<ui->tableWidget->columnCount(); ++i)
    {
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->font();        //获取原有字体设置
        font.setBold(true);                     //设置为粗体
        font.setPointSize(8);                   //字体大小
        headerItem->setTextColor(Qt::blue);     //字体颜色
        headerItem->setFont(font);              //设置字体
        headerItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        itemSize = headerItem->sizeHint();
//        if (headerText.at(i) == "Dir") {
//            itemSize.setWidth(3);
//            headerItem->setSizeHint(itemSize);
//        }

        ui->tableWidget->setHorizontalHeaderItem(i, headerItem); //设置表头单元格的Item
    }

    //ui->tableWidget->setShowGrid(true); //设置显示格子线
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);   //整行选中的方式
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);    //禁止编辑
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);       //行头自适应表格
    //ui->tableWidget->horizontalHeader()->setFont(QFont("song", 12));

    ui->tableWidget->verticalHeader()->setVisible(false);                   // 隐藏垂直表头
    ui->tableWidget->setAlternatingRowColors(true);                         // 设置间隔行底色
    // 设置内容格式
    this->contentRowFont.setPointSize(6);   //字体大小

    connect(ui->toolButton_save, SIGNAL(clicked(bool)), this, SLOT(on_SaveMessage()));
    connect(ui->toolButton_control, SIGNAL(clicked(bool)), this, SLOT(on_toolBtn_control()));
    connect(ui->toolButton_clear, SIGNAL(clicked(bool)), this, SLOT(on_ClearMessage()));
}

trace::~trace()
{
    delete mTrace;
    delete ui;
}
/****************[public members - interface]***********************************************************/

/****************[public members - slots]***************************************************************/
void trace::on_RxTxMessage(QQueue<meassage> *pMsgQue)
{
    traceItemType item;
    meassage msg;
    while (!pMsgQue->isEmpty()) {
        msg = pMsgQue->dequeue();
        //todo: 条件测试用
        item.Id   = msg.Id;
        item.Dlc  = msg.length;
        item.time = msg.timeStamp;
        item.Dir  = (msg.dir == meassage::DIR_TX) ? "Tx" : "Rx";
        memcpy(item.msgData, msg.data, msg.length);
        createItemsARow(currentRow, &item);
        mTrace->append(msg);
    }
    //todo: test code to be delete!
#if (0)
    traceItemType item;
    createItemsARow(currentRow, &item);
#endif
}

//void trace::on_RxTxMessage()
//{
//    traceItemType item;
//    createItemsARow(currentRow, &item);
//}

void trace::on_ClearMessage()
{
    this->totalRow = 0;
    this->currentRow = 0;
    /* ui->tableWidget->clearContents();*/
    int rowIdx = this->ui->tableWidget->rowCount();
    while (rowIdx-- > 0) {
        removeItemsARow(rowIdx);
    }

    /* Clear the buffer of the trace.*/
    mTrace->clear();
}

void trace::on_SaveMessage()
{

}

void trace::on_toolBtn_control()
{
//    if (trace is running)
    {
//      const QString path = (isPaused) ? ":/icon/Resources/icon/start.png" : ":/icon/Resources/icon/pause.png"
        const QIcon icon(QPixmap(":/icon/Resources/icon/start.png"));
        ui->toolButton_control->setIcon(icon);
    }
    qDebug("on control!");
}

void trace::on_toolBtn_scroll()
{

}
/****************[private members]**********************************************************************/
void trace::createItemsARow(int currentRow, traceItemType* p_TraceItem)
{
    QTableWidgetItem* p_item;

    // 插入新的空白行
    ui->tableWidget->insertRow(currentRow);
    ui->tableWidget->setRowHeight(currentRow, 20);

    /* Column 1: Time.*/
    p_item = new QTableWidgetItem(this->msgIcon, QString("%6").arg(currentRow));
    p_item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QFont font = p_item->font();    //获取原有字体设置
    font.setPointSize(6);           //字体大小
    p_item->setFont(font);          //设置字体
    ui->tableWidget->setItem(currentRow, 0, p_item);
    ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(QString("%2").arg(p_TraceItem->time,10,10,QLatin1Char(' '))));
    ui->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(QString("0x%2").arg(p_TraceItem->Id,3,16,QLatin1Char('0'))));
    ui->tableWidget->setItem(currentRow, 3, new QTableWidgetItem(p_TraceItem->Dir));

    QString dataBytes;
    for (int i = 0; i < 8; ++i) {
        dataBytes.append(QString("%2  ").arg(p_TraceItem->msgData[i], 2, 16, QLatin1Char('0')).toUpper());
    }
    ui->tableWidget->setItem(currentRow, 4, new QTableWidgetItem(dataBytes));

    // 滚动到最新行
    ui->tableWidget->scrollToBottom();

    ++this->currentRow;
}

void trace::removeItemsARow(int row)
{
    if (this->totalRow > 0) {
        --this->totalRow;
    }
    ui->tableWidget->removeRow(row);
}

/****************[private members]**********************************************************************/



