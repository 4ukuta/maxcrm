#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmodel.h"

dbmodel MainDb;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainDb.connect_db();
    QSqlQueryModel *model = new QSqlQueryModel (ui->comboBox);
    model->setQuery ("SELECT fio FROM users");
    ui->comboBox->setModel(model);
}

MainWindow::~MainWindow()
{
    MainDb.closeConnetion();
    delete ui;
}
void MainWindow::updateComboBox(){
    ui->comboBox->clear();
    QSqlQueryModel *model = new QSqlQueryModel (ui->comboBox);
    model->setQuery ("SELECT fio FROM users");
    ui->comboBox->setModel(model);
}

void MainWindow::on_pushButton_clicked()
{
    MainDb.addProject(ui->projectname->text(),ui->data_start->text(),ui->data_end->text(),ui->datainfo->toPlainText());
    MainDb.addUser(ui->fio->text(),ui->phone->text(),ui->email->text());
    updateComboBox();
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE fio=?");
    query.addBindValue(ui->comboBox->itemText(ui->comboBox->currentIndex()));
    query.exec();

    query.clear();
    updateComboBox();
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE fio=?");
    query.addBindValue(ui->comboBox->itemText(ui->comboBox->currentIndex()));
    query.exec();
    query.next();
    ui->fio_2->setText(query.value(1).toString());
    ui->email_2->setText(query.value(2).toString());
    ui->phone_2->setText(query.value(3).toString());
    //qDebug(query.value(1).toString().toLatin1());

}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery query;
    query.prepare("UPDATE users SET fio=?,phone=?,email=?  WHERE fio=?");
    query.addBindValue(ui->fio_2->text());
    query.addBindValue(ui->phone_2->text());
    query.addBindValue(ui->email_2->text());
    query.addBindValue(ui->comboBox->itemText(ui->comboBox->currentIndex()));
    query.exec();
    query.clear();
    updateComboBox();
}
