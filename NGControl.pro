#-------------------------------------------------
#
# Project created by QtCreator 2015-01-22T18:05:45
#
#-------------------------------------------------

QT       += core gui \
            serialport   #need it for using serial port

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NGControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    masterthread.cpp

HEADERS  += mainwindow.h \
    masterthread.h

FORMS    += mainwindow.ui
