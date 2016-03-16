#ifndef DBMODEL_H
#define DBMODEL_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "string.h"
#include <QVariant>
#include <QSqlQueryModel>

using namespace std;
class dbmodel
{
private:
    QSqlDatabase db;

public:
    dbmodel();
    bool connect_db();
    QSqlDatabase getConnetionDB();
    void closeConnetion();
    void addUser(QString user, QString phone, QString email);
    void addProject(QString projname,QString dstart,QString dend,QString datainfo,QString);
};

#endif // DBMODEL_H
