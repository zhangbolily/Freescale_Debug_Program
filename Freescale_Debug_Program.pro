#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T15:54:18
#
#-------------------------------------------------

QT       += core gui
QT      += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Freescale_Debug_Program
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    console.cpp \
    settingdialog.cpp \

HEADERS  += mainwindow.h \
    console.h \
    settingdialog.h

RESOURCES += \
    resource.qrc
