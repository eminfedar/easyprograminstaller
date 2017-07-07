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

RESOURCES += \
    qtresource.qrc

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lyaml-cpp
