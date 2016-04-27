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

void InformAct::on_pushButton_clicked()
{
    this->close();
}
void InformAct::getInfo(QString s){
    ui->plainTextEdit->setPlainText(s);
}
