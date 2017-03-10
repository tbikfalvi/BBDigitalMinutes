#-------------------------------------------------
#
# BBDigital Minutes pro file
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE     = app
QT          += core gui xml
DESTDIR      = ..
TARGET       = BBDigitalMinutes

TRANSLATIONS = BBDigitalMinutes_hu.ts

win32:DEFINES -= UNICODE

RC_FILE      = bbdigitalminutes.rc
RESOURCES   += bbdigitalminutes.qrc

HEADERS     += mainwindow.h \
               dlgplayeredit.h \
               dlgedit.h \
               dlgsettings.h \
               csettings.h \
               cplayerpanel.h \
               cminute.h \
               dlglineedit.h

SOURCES     += main.cpp\
               mainwindow.cpp \
               dlgplayeredit.cpp \
               dlgedit.cpp \
               dlgsettings.cpp \
               csettings.cpp \
               cplayerpanel.cpp \
               cminute.cpp \
               dlglineedit.cpp

FORMS       += mainwindow.ui \
               dlgplayeredit.ui \
               dlgedit.ui \
               dlgsettings.ui \
               dlgLineEdit.ui
