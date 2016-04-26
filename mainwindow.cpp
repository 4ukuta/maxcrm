#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmodel.h"

dbmodel MainDb;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    viewUserInfo(false);
    viewProjInfo(false);
    MainDb.connect_db();
    updateComboBox(ui->comboBox);
    updateComboBox(ui->comboBox_2);
    updateComboBox(ui->comboBox_4);
    TableRating();
    log = new Log("log1.out");
   /* Log log("log.out");
    log.addLog("123");*/
    CreateTableByUsers();
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(itemDoubleClicked(QListWidgetItem *)));
}

MainWindow::~MainWindow()
{
    MainDb.closeConnetion();
    delete ui;
}
void MainWindow::viewUserInfo(bool t){
    ui->listView->setVisible(t);
    ui->label_13->setVisible(t);
    ui->label_15->setVisible(t);
    ui->label_16->setVisible(t);
    ui->label_17->setVisible(t);
    ui->label_18->setVisible(t);
    ui->label_19->setVisible(t);
}
void MainWindow::viewProjInfo(bool t){
    ui->listView_2->setVisible(t);
    ui->label_36->setVisible(t);
    ui->label_35->setVisible(t);
    ui->label_34->setVisible(t);
    ui->label_33->setVisible(t);
    ui->label_32->setVisible(t);
    ui->label_21->setVisible(t);
    ui->label_31->setVisible(t);
    ui->label_30->setVisible(t);
    ui->label_29->setVisible(t);
    ui->label_20->setVisible(t);
    ui->label_22->setVisible(t);
    ui->plainTextEdit->setVisible(t);
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
    CreateTableByUsers();
    log->addLog("Добавлен клиент: "+ ui->fio->text()+",телефон: "+ui->phone->text() + ",email: " + ui->email->text());
}

void MainWindow::CreateTableByUsers(){
    ui->listWidget->clear();
    QSqlQuery query;
    query.prepare("SELECT * FROM users");

    query.exec();
    while(query.next()){
        QListWidgetItem* item = new QListWidgetItem(query.value(1).toString(), ui->listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
        item->setCheckState(Qt::Unchecked); // AND initialize check state
    }
}
void MainWindow::itemDoubleClicked(QListWidgetItem* listWidgetItem) {
    QString name = listWidgetItem->text();


    if(strstat == 1){
        pstr = name;
        viewProjInfo(true);
        infopstatus = 1;
        QSqlQuery query;
        query.prepare("SELECT * FROM projects WHERE project_name = ?");
        query.addBindValue(QVariant(pstr));
        query.exec();
        query.next();
        ui->label_32->setText(namestr);
        ui->label_33->setText(pstr);
        ui->label_34->setText(query.value(2).toDate().toString());
        ui->label_35->setText(query.value(3).toDate().toString());
        ui->label_36->setText(query.value(5).toString());
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(query.value(4).toString());
    }
    if(strstat == 0){

        ui->listWidget->clear();
        QSqlQuery query;
        query.prepare("SELECT project_name FROM user_project_links WHERE fio = ?");
        query.addBindValue(QVariant(name));
        query.exec();
        while(query.next()){
            ui->listWidget->addItem(query.value(0).toString());
        }
        namestr = name;
        strstat++;
        ui->pushButton_9->setDisabled(true);
    }

}
void MainWindow::on_pushButton_3_clicked()
{


    QSqlQuery query1;
    query1.prepare("SELECT COUNT(*) FROM user_project_links WHERE fio=?");
    query1.addBindValue(ui->comboBox->itemText(ui->comboBox->currentIndex()));
    query1.exec();
    query1.next();
    if(query1.value(0).toInt()>0){

        Inform *inf = new Inform();
        QObject::connect(this, SIGNAL(setName(QString)),
                   inf, SLOT(getName(QString)));
         QRect geo = this->geometry();
        inf->move(geo.x()+this->width()/2-inf->width()/2,geo.y()+this->height()/2-inf->height()/2);
        emit setName(ui->comboBox->itemText(ui->comboBox->currentIndex()));
        inf->show();
    }else{
        QSqlQuery query;
            query.prepare("DELETE FROM users WHERE fio=?");
            query.addBindValue(ui->comboBox->itemText(ui->comboBox->currentIndex()));
            query.exec();

            query.clear();
            log->addLog("Удаление клиент: "+ ui->comboBox->itemText(ui->comboBox->currentIndex()));
            updateComboBox(ui->comboBox);
            updateComboBox(ui->comboBox_2);
            updateComboBox(ui->comboBox_4);
    }

    query1.clear();
    CreateTableByUsers();
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
    CreateTableByUsers();
    log->addLog("Обновление клиент: "+ ui->fio_2->text()+",телефон: "+ui->phone_2->text() + ",email: " + ui->email_2->text());
}

void MainWindow::on_pushButton_4_clicked()
{
    MainDb.addProject(ui->projectname->text(),ui->data_start->text(),ui->data_end->text(),ui->datainfo->toPlainText(),ui->comboBox_2->itemText(ui->comboBox_2->currentIndex()));
    updateComboBox(ui->comboBox);
    updateComboBox(ui->comboBox_2);
    updateComboBox(ui->comboBox_4);
    CreateTableByUsers();
    log->addLog("Добавлен проект: "+ ui->projectname->text()+",дата начала: "+ui->data_start->text() + ",дата окончания: " + ui->data_end->text() + ",информация: " + ui->datainfo->toPlainText());
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
    ui->horizontalSlider->setValue(query.value(5).toInt());
    QString s = QString::number(query.value(5).toInt());
    ui->label_12->setText(s);
    query.clear();
}

void MainWindow::on_pushButton_7_clicked()
{
    QSqlQuery query;
    query.prepare("UPDATE projects SET project_name=?, date_begin=?,date_end=?,add_info=?,rating=? WHERE project_name=?");
    query.addBindValue(ui->projectname_3->text());
    query.addBindValue(ui->data_start_3->text());
    query.addBindValue(ui->data_end_3->text());
    query.addBindValue(ui->datainfo_3->toPlainText());
    query.addBindValue(ui->horizontalSlider->value());
    query.addBindValue(ui->comboBox_5->itemText(ui->comboBox_5->currentIndex()));

    query.exec();
    query.clear();

    QSqlQuery query1;
    query1.prepare("UPDATE user_project_links SET rating=? WHERE fio=? AND project_name=?");
    query1.addBindValue(ui->horizontalSlider->value());
    query1.addBindValue(ui->comboBox_4->itemText(ui->comboBox_4->currentIndex()));
    query1.addBindValue(ui->comboBox_5->itemText(ui->comboBox_5->currentIndex()));
    query1.exec();
    query1.clear();
    log->addLog("Обновление проект: "+ ui->projectname_3->text()+",дата начала: "+ui->data_start_3->text() + ",дата окончания: " + ui->data_end_3->text() + ",информация: " + ui->datainfo_3->toPlainText() + ",рейтинг:" + QString::number(ui->horizontalSlider->value()));
}

void MainWindow::on_pushButton_8_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM projects WHERE project_name=?");
    query.addBindValue(ui->comboBox_5->itemText(ui->comboBox_5->currentIndex()));
    query.exec();
    query.clear();

    QSqlQuery query1;
    query1.prepare("DELETE FROM user_project_links WHERE project_name=? AND fio=?");
    query1.addBindValue(ui->comboBox_5->itemText(ui->comboBox_5->currentIndex()));
    query1.addBindValue(ui->comboBox_4->itemText(ui->comboBox_4->currentIndex()));
    query1.exec();
    query1.clear();
    log->addLog("Удаление проект: "+ ui->comboBox_5->itemText(ui->comboBox_5->currentIndex()));
    updateComboBox(ui->comboBox);
    updateComboBox(ui->comboBox_2);
    updateComboBox(ui->comboBox_4);
    CreateTableByUsers();
}

void MainWindow::on_horizontalSlider_rangeChanged(int min, int max)
{

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int va = value;
    QString s = QString::number(va);
    ui->label_12->setText(s);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    int va = index;
    if(va == 2){
        TableRating();
    }
    CreateTableByUsers();

}
void MainWindow::TableRating(){
    QSqlQuery query;
    query.prepare("SELECT fio,SUM(rating),count(fio) FROM user_project_links group by fio");
    query.exec();
    int j = 0;
    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }
    while(query.next()){
        ui->tableWidget->insertRow(j);
         QTableWidgetItem* newItem = new QTableWidgetItem(query.value(0).toString());
        ui->tableWidget->setItem(j,0,newItem);
        float a = query.value(1).toFloat();
        float b = query.value(2).toFloat();

        float x = a/b;
        QString s;
        s.setNum(x);
        newItem = new QTableWidgetItem(s);
        ui->tableWidget->setItem(j,1,newItem);

    }
    query.clear();
}

void MainWindow::on_pushButton_9_clicked()
{
    viewUserInfo(true);
    QString name = ui->listWidget->currentItem()->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE fio=?");
    query.addBindValue(name);
    query.exec();
    query.next();
    ui->label_17->setText(query.value(1).toString());
    ui->label_19->setText(query.value(2).toString());
    ui->label_18->setText(query.value(3).toString());
    infoustatus = 1;
}

void MainWindow::on_pushButton_5_clicked()
{
    if(infoustatus == 1){
        CreateTableByUsers();
        viewUserInfo(false);
        infoustatus = 0;
    }

    if(infopstatus == 1){
        viewProjInfo(false);
        infopstatus = 0;
        /*ui->listWidget->clear();
        QSqlQuery query;
        query.prepare("SELECT project_name FROM user_project_links WHERE fio = ?");
        query.addBindValue(QVariant(pstr));
        query.exec();
        while(query.next()){
            ui->listWidget->addItem(query.value(0).toString());
        }*/
    }else{
        if(strstat == 1){
            CreateTableByUsers();
            ui->pushButton_9->setDisabled(false);
            strstat--;
        }
    }



}

void MainWindow::on_pushButton_6_clicked()
{
    QFile file("allinfo.data");
    file.open(QFile::WriteOnly|QFile::Truncate);
    QDate dateToday = QDate::currentDate();


    file.write(dateToday.toString().toUtf8() + "\n");

    int j = 1;
    for(int row = 0; row < ui->listWidget->count(); row++)
    {
        QListWidgetItem *item = ui->listWidget->item(row);
        if(item->checkState() == Qt::Checked){
            file.write(QString::number(j).toLatin1() +") ФИО:" +item->text().toUtf8() + "\n");
            QSqlQuery query;
            query.prepare("SELECT project_name FROM user_project_links WHERE fio = ?");
            query.addBindValue(QVariant(item->text()));
            query.exec();
            int k = 1;
            while(query.next()){
                file.write(QString::number(j).toLatin1()+"."+QString::number(k).toLatin1()+") Название проекта:" +query.value(0).toString().toUtf8() + "\n");
                QSqlQuery query1;
                query1.prepare("SELECT * FROM projects WHERE project_name = ?");
                query1.addBindValue(QVariant(query.value(0)));
                query1.exec();
                query1.next();
                file.write("Дата начала:" +query1.value(2).toDate().toString().toUtf8() + "\n");
                file.write("Дата окончания:" +query1.value(3).toDate().toString().toUtf8() + "\n");
                file.write("Рейтинг:" +query1.value(5).toString().toUtf8() + "\n");
                file.write("Информация:" +query1.value(4).toString().toUtf8() + "\n");
                k++;
            }
            j++;
        }
    }
    file.close();
}
