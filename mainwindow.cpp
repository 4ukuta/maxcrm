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
    updateComboBox(ui->comboBox);
    updateComboBox(ui->comboBox_2);
    updateComboBox(ui->comboBox_4);
}

MainWindow::~MainWindow()
{
    MainDb.closeConnetion();
    delete ui;
}
void MainWindow::updateComboBox(QComboBox *cmb){
    cmb->clear();
    QSqlQueryModel *model = new QSqlQueryModel (cmb);
    model->setQuery ("SELECT fio FROM users");
    cmb->setModel(model);
}
void MainWindow::updateComboBoxProj(QComboBox *cmb){
    cmb->clear();
    QSqlQueryModel *model = new QSqlQueryModel (cmb);
    model->setQuery ("SELECT project_name FROM projects");
    cmb->setModel(model);
}
void MainWindow::on_pushButton_clicked()
{
    MainDb.addUser(ui->fio->text(),ui->phone->text(),ui->email->text());
    updateComboBox(ui->comboBox);
    updateComboBox(ui->comboBox_2);
    updateComboBox(ui->comboBox_4);
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE fio=?");
    query.addBindValue(ui->comboBox->itemText(ui->comboBox->currentIndex()));
    query.exec();

    query.clear();
    updateComboBox(ui->comboBox);
    updateComboBox(ui->comboBox_2);
    updateComboBox(ui->comboBox_4);
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
    updateComboBox(ui->comboBox);
    updateComboBox(ui->comboBox_2);
    updateComboBox(ui->comboBox_4);
}

void MainWindow::on_pushButton_4_clicked()
{
    MainDb.addProject(ui->projectname->text(),ui->data_start->text(),ui->data_end->text(),ui->datainfo->toPlainText(),ui->comboBox_2->itemText(ui->comboBox_2->currentIndex()));
    updateComboBox(ui->comboBox);
    updateComboBox(ui->comboBox_2);
    updateComboBox(ui->comboBox_4);
}

void MainWindow::on_comboBox_4_currentIndexChanged(const QString &arg1)
{

}

void MainWindow::on_comboBox_4_currentTextChanged(const QString &arg1)
{
    ui->comboBox_5->clear();
    QSqlQuery query;
    query.prepare("SELECT project_name FROM user_project_links WHERE fio = ?");
    query.addBindValue(QVariant(ui->comboBox_4->itemText(ui->comboBox_4->currentIndex())));
    query.exec();
    while(query.next()){
       ui->comboBox_5->addItem(query.value(0).toString());
    }
    query.clear();
}

void MainWindow::on_comboBox_5_currentTextChanged(const QString &arg1)
{
    /*ui->comboBox_5->clear();
    QSqlQuery query123;
    query123.prepare("SELECT * FROM projects WHERE project_name = ?");
    query123.addBindValue(QVariant(ui->comboBox_5->itemText(ui->comboBox_5->currentIndex())));
    query123.exec();
    query123.clear();
   // ui->projectname_3->setText(query.value(0).toString());*/
}

void MainWindow::on_comboBox_5_currentIndexChanged(const QString &arg1)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM projects WHERE project_name = ?");
    query.addBindValue(QVariant(ui->comboBox_5->itemText(ui->comboBox_5->currentIndex())));
    query.exec();
    query.next();
    ui->projectname_3->setText(query.value(1).toString());
    ui->data_start_3->setDate(query.value(2).toDate());
    ui->data_end_3->setDate(query.value(3).toDate());
    ui->datainfo_3->clear();
    ui->datainfo_3->appendPlainText(query.value(4).toString());
    query.clear();
}
