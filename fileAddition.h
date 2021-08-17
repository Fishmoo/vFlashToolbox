#ifndef FILEADDITION_H
#define FILEADDITION_H

#include <QWidget>

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
};

#endif // FILEADDITION_H
