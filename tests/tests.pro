#-------------------------------------------------
#
# Project created by QtCreator 2016-03-16T15:26:49
#
#-------------------------------------------------

QT       += core sql

QT       -= gui

TARGET = tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
QTPLUGIN += qsqlmysql

SOURCES += main.cpp ../dbmodel.cpp
