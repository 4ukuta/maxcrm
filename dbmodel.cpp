#include "dbmodel.h"
#include "qdebug.h"


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
    return ok;
}

QSqlDatabase dbmodel::getConnetionDB(){
    return this->db;
}
void dbmodel::closeConnetion(){
    db.close();
}
void dbmodel::addProject(QString projname,QString dstart,QString dend,QString datainfo,QString user_name){
    QSqlQuery query;
    query.prepare("INSERT INTO projects (project_name,date_begin,date_end,add_info,rating) "
             "VALUES (?,?,?,?,?)");

    query.addBindValue(QVariant(projname));
    query.addBindValue(QVariant(dstart));
    query.addBindValue(QVariant(dend));
    query.addBindValue(QVariant(datainfo));
    query.addBindValue(QVariant(0));
    query.exec();
    QVariant last_id = query.lastInsertId();
    query.clear();

    QSqlQuery query_id_for_user;
    query_id_for_user.prepare("SELECT id FROM users WHERE fio=?");
    query_id_for_user.addBindValue(user_name);
    query_id_for_user.exec();
    query_id_for_user.next();

    QString id_user = query_id_for_user.value(0).toString();
    QSqlQuery query1;
    query1.prepare("INSERT INTO user_project_links (user_id,fio,project_id,project_name,rating) VALUES (?,?,?,?,?)");

    query1.addBindValue(QVariant(id_user));
    query1.addBindValue(user_name);
    query1.addBindValue(last_id);
    query1.addBindValue(projname);
    query1.addBindValue(0);
    bool d = query1.exec();
    query1.clear();
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
