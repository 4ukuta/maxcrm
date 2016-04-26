#include "informact.h"
#include "ui_informact.h"

InformAct::InformAct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InformAct)
{
    ui->setupUi(this);
}

InformAct::~InformAct()
{
    delete ui;
}
