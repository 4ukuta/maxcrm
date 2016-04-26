#include "projinfo.h"
#include "ui_projinfo.h"

ProjInfo::ProjInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjInfo)
{
    ui->setupUi(this);
}

ProjInfo::~ProjInfo()
{
    delete ui;
}
