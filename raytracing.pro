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
    model/wireframe.cpp \
    model/light.cpp \
    model/primitive.cpp \
    model/box.cpp \
    model/eye.cpp \
    model/matrix.cpp \
    model/camera.cpp \
    model/sphere.cpp \
    model/polygon.cpp \
    model/quadric.cpp \
    model/quadrobox.cpp \
    model/renderset.cpp \
    io/io.cpp \
    model/scene.cpp \
    ctrl/doc.cpp \
    ctrl/params.cpp

HEADERS  += mainwindow.h \
    model/point.h \
    model/segment.h \
    model/ray.h \
    model/color.h \
    model/wireframe.h \
    model/light.h \
    model/primitive.h \
    model/box.h \
    model/eye.h \
    model/matrix.h \
    model/camera.h \
    model/sphere.h \
    model/polygon.h \
    model/common.h \
    model/quadric.h \
    model/quadrobox.h \
    model/renderset.h \
    io/io.h \
    model/scene.h \
    ctrl/doc.h \
    ctrl/params.h

FORMS    += mainwindow.ui
