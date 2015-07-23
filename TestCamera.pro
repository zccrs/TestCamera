#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T10:22:25
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestCamera
TEMPLATE = app


SOURCES += main.cpp\
    form.cpp \
    #cameraformatproxy.cpp \
    cameraview.cpp

HEADERS  += \
    form.h \
    #cameraformatproxy.h \
    cameraview.h

FORMS += \
    form.ui
