#include "fileAddition.h"
#include "ui_fileAddition.h"
#include <QDebug>

fileAddition::fileAddition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileAddition),
    mFileUrls(new QList<QUrl>)
{
    ui->setupUi(this);

    connect(ui->btnAdd,    &QToolButton::pressed, this, &fileAddition::on_toolBtn_add);
    connect(ui->btnRemove, &QToolButton::pressed, this, &fileAddition::on_toolBtn_rm);
    connect(ui->btnUp,     &QToolButton::pressed, this, &fileAddition::on_toolBtn_up);
    connect(ui->btnDown,   &QToolButton::pressed, this, &fileAddition::on_toolBtn_down);

    // 设置trace 行表头 & 列数
//    QStringList headerText;
//    headerText <<"No" << "File name" << "Type";
//    ui->tableWidget->setColumnCount(headerText.count());
//    QTableWidgetItem *headerItem;
//    ui->tableWidget->horizontalHeader()->setMinimumSectionSize(30);
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
//    QSize itemSize;
//    for (int i=0; i<ui->tableWidget->columnCount(); ++i) {
//        headerItem = new QTableWidgetItem(headerText.at(i));
//        QFont font = headerItem->font();        //获取原有字体设置
//        font.setBold(true);                     //设置为粗体
//        font.setPointSize(8);                   //字体大小
//        headerItem->setTextColor(Qt::blue);     //字体颜色
//        headerItem->setFont(font);              //设置字体
//        headerItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//        itemSize = headerItem->sizeHint();
////        headerItem->setSizeHint(itemSize);
//        ui->tableWidget->setHorizontalHeaderItem(i, headerItem); //设置表头单元格的Item
//    }
}

fileAddition::~fileAddition()
{
//    ui->tableWidget->clear();
    delete mFileUrls;
    delete ui;
}

/****************[public members - slots]***************************************************************/
void fileAddition::on_toolBtn_add()
{
    QList<QUrl> filesUrl = QFileDialog::getOpenFileUrls(this, \
        tr("Open binary files"), tr("."), tr("bin(*.hex*.s19*.bin);;all(*)"));
    if (!filesUrl.isEmpty()) {
        mFileUrls->append(filesUrl);
//        createItemsARow(filesUrl.at(0));
    }
    qDebug() << "ToolButton add pressed!";
}

void fileAddition::on_toolBtn_rm()
{
    qDebug() << "ToolButton remove pressed!";
}

void fileAddition::on_toolBtn_up()
{
    qDebug() << "ToolButton up pressed!";
}

void fileAddition::on_toolBtn_down()
{
    qDebug() << "ToolButton down pressed!";
}

/****************[private members]**********************************************************************/
void fileAddition::createItemsARow(const QUrl &fileUrl)
{
    QTableWidgetItem* p_item;

    //todo: 没有选择则是最后一行, 否则为选择的后一行
    int currentRow = 1;

    // 插入新的空白行
//    ui->tableWidget->insertRow(currentRow);
//    ui->tableWidget->setRowHeight(currentRow, 20);

    /* Column 1: Time.*/
//    p_item = new QTableWidgetItem(this->msgIcon, QString("%6").arg(currentRow));
//    p_item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

//    QFont font = p_item->font();    //获取原有字体设置
//    font.setPointSize(6);           //字体大小
//    p_item->setFont(font);          //设置字体
//    ui->tableWidget->setItem(currentRow, 0, p_item);
//    ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(fileUrl.fileName()));
//    ui->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(QString("0x%2").arg(p_TraceItem->Id,3,16,QLatin1Char('0'))));
//    ui->tableWidget->setItem(currentRow, 3, new QTableWidgetItem(p_TraceItem->Dir));

//    QString dataBytes;
//    for (int i = 0; i < 8; ++i) {
//        dataBytes.append(QString("%2  ").arg(p_TraceItem->msgData[i], 2, 16, QLatin1Char('0')).toUpper());
//    }
//    ui->tableWidget->setItem(currentRow, 4, new QTableWidgetItem(dataBytes));

//    // 滚动到最新行
//    ui->tableWidget->scrollToBottom();

//    ++this->currentRow;
}

void fileAddition::removeItemsARow(const int selectRow)
{
//    if (this->totalRow > 0) {
//        --this->totalRow;
//    }
//    ui->tableWidget->removeRow(row);
}
