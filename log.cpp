#include "log.h"
#include <QDate>

Log::Log(QString file)
{
   this->filename = file;
}
void Log::addLog(QString mess){
    QFile file(this->filename);
    QDate dateToday = QDate::currentDate();

    if (file.open(QIODevice::Append)) {
       file.write(dateToday.toString().toUtf8() + ": " + mess.toUtf8() + "\n");
    }
    file.close();
}
