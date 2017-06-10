#-------------------------------------------------
#
# Project created by QtCreator 2017-05-31T16:42:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyProgramInstaller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG  += c++11

RESOURCES += \
    qtresource.qrc

LIBS += -lyaml-cpp
