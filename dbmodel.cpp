#include "dbmodel.h"



dbmodel::dbmodel()
{

}
bool dbmodel::connect_db()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("maxcrm");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();
}

QSqlDatabase dbmodel::getConnetionDB(){
    return this->db;
}
void dbmodel::closeConnetion(){
    db.close();
}
void dbmodel::addProject(QString projname,QString dstart,QString dend,QString datainfo){
    QSqlQuery query;
    query.prepare("INSERT INTO projects (project_name,date_begin,date_end,add_info) "
             "VALUES (?,?,?,?)");

    query.addBindValue(QVariant(projname));
    query.addBindValue(QVariant(dstart));
    query.addBindValue(QVariant(dend));
    query.addBindValue(QVariant(datainfo));
    query.exec();
    query.clear();
}

void dbmodel::addUser(QString user, QString phone, QString email){
    QSqlQuery query;
    query.prepare("INSERT INTO users (fio,phone,email) "
             "VALUES (?,?,?)");

    query.addBindValue(QVariant(user));
    query.addBindValue(QVariant(phone));
    query.addBindValue(QVariant(email));
    query.exec();

    query.clear();

}
