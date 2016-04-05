#include "inform.h"
#include "ui_inform.h"

Inform::Inform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inform)
{
    ui->setupUi(this);
}

Inform::~Inform()
{
    delete ui;
}
void Inform::getName(QString name){
    ui->label->setText("Нельзя удалить клиента: "+name + ". Т.к. он имеет проекты!!!");
}
