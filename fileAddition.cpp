#include "fileAddition.h"
#include "ui_fileAddition.h"
#include <QDebug>
#include <QFileInfo>
#include <QFileIconProvider>

fileAddition::fileAddition(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::fileAddition)
    ,mFileUrls(new QList<QUrl>)
    ,mFileNo(0U)
{
    ui->setupUi(this);

    connect(ui->btnAdd,    &QToolButton::pressed, this, &fileAddition::on_toolBtn_add);
    connect(ui->btnRemove, &QToolButton::pressed, this, &fileAddition::on_toolBtn_rm);
    connect(ui->btnUp,     &QToolButton::pressed, this, &fileAddition::on_toolBtn_up);
    connect(ui->btnDown,   &QToolButton::pressed, this, &fileAddition::on_toolBtn_down);
//    connect(ui->tableWidget, &QTableWidget::)

    /* 设置列表头*/
    ui->tableWidget->verticalHeader()->setVisible(false);

    // 设置trace 行表头 & 列数
    QStringList headerText;
    headerText <<"No" << "    File name" << "Type" << "DigestAlgr" << "Path";
    ui->tableWidget->setColumnCount(headerText.count());
    QTableWidgetItem *headerItem;
//    ui->tableWidget->horizontalHeader()->setMinimumSectionSize(20);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    QSize itemSize;
    for (int i=0; i<ui->tableWidget->columnCount(); ++i) {
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->font();        //获取原有字体设置
        font.setBold(true);                     //设置为粗体
        font.setPointSize(8);                   //字体大小
        headerItem->setTextColor(Qt::blue);     //字体颜色
        headerItem->setFont(font);              //设置字体
        headerItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        itemSize = headerItem->sizeHint();
//        headerItem->setSizeHint(itemSize);
        ui->tableWidget->setHorizontalHeaderItem(i, headerItem); //设置表头单元格的Item
    }
}

fileAddition::~fileAddition()
{
    ui->tableWidget->clear();
    delete mFileUrls;
    delete ui;
}

/****************[public members - slots]***************************************************************/
void fileAddition::on_toolBtn_add()
{
    QList<QUrl> filesUrl = QFileDialog::getOpenFileUrls(this, \
        tr("Open binary files"), tr("."), tr("all(*);;bin(*.hex*.s19*.bin)"));
    if (!filesUrl.isEmpty()) {
        QList<QTableWidgetItem *> itemSelected = ui->tableWidget->selectedItems();
        if (!itemSelected.isEmpty()) {
            this->_selectFileRow = itemSelected.first()->row() + 1;
        } else {
            this->_selectFileRow = ui->tableWidget->rowCount();
        }
        mFileUrls->append(filesUrl);
        for (int i = 0; i < filesUrl.size(); ++i) {
            createItemsARow(filesUrl.at(i), (this->_selectFileRow)++);
        }
    }

    if (mFileUrls->size() > 0) {



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

void fileAddition::on_ItemCellSelected()
{
    qDebug() << "ItemCellSelected!";
}

/****************[private members]**********************************************************************/
void fileAddition::createItemsARow(const QUrl &fileUrl, const int whichRow)
{
#if (1)
    QTableWidget *tableWdg = ui->tableWidget;
    QTableWidgetItem* p_item;

    //todo: 没有选择则是最后一行, 否则为选择的后一行
    const int currentRow = static_cast<int>(whichRow);

    // 插入新的空白行
    ui->tableWidget->insertRow(currentRow);
    ui->tableWidget->setRowHeight(currentRow, 20);

    /* Column 1: No.*/
    p_item = new QTableWidgetItem(QString("%6").arg(currentRow));
    p_item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableWidget->setItem(currentRow, 0, p_item);

    /* Column 2: File name.*/
    QFont font = p_item->font();    //获取原有字体设置
    font.setPointSize(6);           //字体大小
    p_item->setFont(font);          //设置字体

#ifndef __SYSTEM_DEFAULT_FILE_QICON
    QFileInfo fileInfo(QFile(fileUrl.fileName()));
    QFileIconProvider provider;
    ui->tableWidget->setItem(currentRow, 1,
        new QTableWidgetItem(provider.icon(fileInfo), fileUrl.fileName()));
#else
    ui->tableWidget->setItem(currentRow, 1,
        new QTableWidgetItem(QIcon(QPixmap(":/file/Resources/file/File.png")), fileUrl.fileName()));
#endif
    /* Column 3: File type.*/

    /* Column 4: Digest Algorithm.*/

    /* Column 5: File path.*/
    ui->tableWidget->setItem(currentRow, 4, new QTableWidgetItem(fileUrl.path()));

//    ui->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(QString("0x%2").arg(p_TraceItem->Id,3,16,QLatin1Char('0'))));
//    ui->tableWidget->setItem(currentRow, 3, new QTableWidgetItem(p_TraceItem->Dir));

    // 滚动到最新行
    ui->tableWidget->scrollToBottom();

//    ++this->currentRow;
#endif
}

void fileAddition::removeItemsARow(const int selectRow)
{
#if (0)
    if (this->totalRow > 0) {
        --this->totalRow;
    }
    ui->tableWidget->removeRow(row);
#endif
}

//QIcon fileAddition::getFileIcon(const QFile& file_name)
//{
//    QIcon icon = QIcon(":/file/Resources/file/File.png");
//    QFileIconProvider icon_provider;
//    QTemporaryFile tmp_file(QDir::tempPath() + QDir::separator() +
//    QCoreApplication::applicationName() + "_XXXXXX" + file_name.e);
//    tmp_file.setAutoRemove(false);

//    if(tmp_file.open())
//    {
//    QString file_name = tmp_file.fileName();
//    tmp_file.write(QByteArray());
//    tmp_file.close();

//    icon = icon_provider.icon(QFileInfo(file_name));
//    tmp_file.remove();
//    }
//    else
//    {
//    qCritical()<<QString("failed to write temporary file %1") .arg(tmp_file.fileName());
//    }

//    return icon;
//}
