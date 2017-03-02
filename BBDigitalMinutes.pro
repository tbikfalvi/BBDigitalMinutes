#-------------------------------------------------
#
# Project created by QtCreator 2017-02-12T10:26:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BBDigitalMinutes
TEMPLATE = app

RESOURCES   += bbdigitalminutes.qrc
RC_FILE      = bbdigitalminutes.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    dlgplayeredit.cpp \
    dlgedit.cpp

HEADERS  += mainwindow.h \
    dlgplayeredit.h \
    dlgedit.h

FORMS    += mainwindow.ui \
    dlgplayeredit.ui \
    dlgedit.ui
