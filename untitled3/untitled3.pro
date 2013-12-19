#-------------------------------------------------
#
# Project created by QtCreator 2013-12-19T22:22:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        qaxiszoomsvc.cpp\
        qwheelzoomsvc.cpp\
        qwtchartzoom.cpp


HEADERS += mainwindow.h\
        qaxiszoomsvc.h\
        qwheelzoomsvc.h\
        qwtchartzoom.h


FORMS    += mainwindow.ui
INCLUDEPATH += /usr/include/qwt6/
LIBS += -lqwt6
