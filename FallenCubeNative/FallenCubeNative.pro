#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T19:55:52
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FallenCubeNative
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filedownloader.cpp \
    zipdecompress.cpp \
    miniz.cpp \
    download.cpp

HEADERS  += mainwindow.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/reader.h \
    json/value.h \
    json/writer.h \
    filedownloader.h \
    zipdecompress.h \
    download.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
