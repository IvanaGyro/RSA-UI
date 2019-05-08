#-------------------------------------------------
#
# Project created by QtCreator 2015-12-26T11:00:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RSA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bigint.cpp \
    func_bigint.cpp

HEADERS  += mainwindow.h \
    bigint.h \
    func_bigint.h

FORMS    += mainwindow.ui
