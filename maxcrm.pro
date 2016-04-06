#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T11:00:12
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = maxcrm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbmodel.cpp \
    inform.cpp \
    log.cpp

HEADERS  += mainwindow.h \
    dbmodel.h \
    inform.h \
    log.h
QTPLUGIN += qsqlmysql
FORMS    += mainwindow.ui \
    inform.ui
