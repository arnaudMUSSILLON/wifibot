#-------------------------------------------------
#
# Project created by QtCreator 2018-02-16T14:28:27
#
#-------------------------------------------------

QT       += core gui network webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wifibot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controler.cpp

HEADERS  += mainwindow.h \
    controler.h

FORMS    += mainwindow.ui
