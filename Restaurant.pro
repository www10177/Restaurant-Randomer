#-------------------------------------------------
#
# Project created by QtCreator 2016-07-23T14:30:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Restaurant
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        addnewdialog.cpp \
    rolldialog.cpp

HEADERS  += mainwindow.h \
         addnewdialog.h \
    rolldialog.h

FORMS    += mainwindow.ui \
         addnewdialog.ui \
    rolldialog.ui

DISTFILES += \
    Memo
