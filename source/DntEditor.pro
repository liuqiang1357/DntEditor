#-------------------------------------------------
#
# Project created by QtCreator 2014-01-12T17:56:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DntEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \

HEADERS  += mainwindow.h \

FORMS    += mainwindow.ui

OTHER_FILES += \
    myRc.rc

RC_FILE = \
    myRc.rc
QT +=  xml

include(qtxlsx/xlsx/qtxlsx.pri)


