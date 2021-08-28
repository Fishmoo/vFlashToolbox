#ifndef FILEADDITION_H
#define FILEADDITION_H

#include <QWidget>
#include <QFile>
#include <QUrl>
#include <QList>
#include <QFileDialog>

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

private:
    Ui::fileAddition *ui;
    QList<QUrl>      *mFileUrls;
    void createItemsARow(const QUrl &fileUrl);
    void removeItemsARow(const int selectRow);
};

#endif // FILEADDITION_H
