#include "fileAddition.h"
#include "ui_fileAddition.h"

fileAddition::fileAddition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileAddition)
{
    ui->setupUi(this);
}

fileAddition::~fileAddition()
{
    delete ui;
}
