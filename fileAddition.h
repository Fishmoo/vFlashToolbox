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

private:
    Ui::fileAddition *ui;
};

#endif // FILEADDITION_H
