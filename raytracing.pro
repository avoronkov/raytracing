#-------------------------------------------------
#
# Project created by QtCreator 2017-02-24T08:16:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = raytracing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model/point.cpp \
    model/segment.cpp \
    model/ray.cpp \
    model/color.cpp \
    model/wireframe.cpp

HEADERS  += mainwindow.h \
    model/point.h \
    model/segment.h \
    model/ray.h \
    model/color.h \
    model/wireframe.h

FORMS    += mainwindow.ui
