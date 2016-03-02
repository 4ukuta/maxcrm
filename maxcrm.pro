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
    dbmodel.cpp

HEADERS  += mainwindow.h \
    dbmodel.h
QTPLUGIN += qsqlmysql
FORMS    += mainwindow.ui
