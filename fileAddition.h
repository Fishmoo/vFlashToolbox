#ifndef FILEADDITION_H
#define FILEADDITION_H

#include <QWidget>
#include <QFile>
#include <QUrl>
#include <QList>
#include <QFileDialog>
#include <QTableWidgetItem>

#define __SYSTEM_DEFAULT_FILE_QICON

namespace Ui {
class fileAddition;
}

class fileAddition : public QWidget
{
    Q_OBJECT

public:
    explicit fileAddition(QWidget *parent = nullptr);
    ~fileAddition();

public slots:
    void on_toolBtn_add();
    void on_toolBtn_rm();
    void on_toolBtn_up();
    void on_toolBtn_down();
    void on_ItemCellSelected();

private:
    Ui::fileAddition *ui;
    QList<QUrl>      *mFileUrls;
    qint8             mFileNo;
    QList<QTableWidgetItem *> _itemsSelected;
    int             _selectFileRow;

    void  createItemsARow(const QUrl &fileUrl, const int whichRow);
    void  removeItemsARow(const int selectRow);
};

#endif // FILEADDITION_H
