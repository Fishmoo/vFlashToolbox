#include "fileAddition.h"
#include "ui_fileAddition.h"
#include <QDebug>

fileAddition::fileAddition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileAddition)
{
    ui->setupUi(this);
    connect(ui->btnAdd,    &QToolButton::pressed, this, &fileAddition::on_toolBtn_add);
    connect(ui->btnRemove, &QToolButton::pressed, this, &fileAddition::on_toolBtn_rm);
    connect(ui->btnUp,     &QToolButton::pressed, this, &fileAddition::on_toolBtn_up);
    connect(ui->btnDown,   &QToolButton::pressed, this, &fileAddition::on_toolBtn_down);
}

fileAddition::~fileAddition()
{
    delete ui;
}

/****************[public members - slots]***************************************************************/
void fileAddition::on_toolBtn_add()
{
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
