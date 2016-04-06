#ifndef LOG_H
#define LOG_H

#include <QFile>

class Log
{
public:
    Log(QString);
    void addLog(QString mess);
    QString filename;
private:

};

#endif // LOG_H
