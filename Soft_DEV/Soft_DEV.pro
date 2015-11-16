#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T03:19:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Soft_DEV
CONFIG += console
CONFIG -= app_bundle
CONFIG += x86_64
CONFIG -= i386
LIBS += -lssl -lcrypto
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mainpage.cpp \
    chatpage.cpp \
    chatcontextlistitem.cpp \
    chatcontectlistitem_s.cpp

HEADERS  += widget.h \
    mainpage.h \
    chatpage.h \
    classinfo.h \
    chatcontextlistitem.h \
    chatcontectlistitem_s.h

FORMS    += widget.ui \
    mainpage.ui \
    chatpage.ui \
    chatcontextlistitem.ui \
    chatcontectlistitem_s.ui

RESOURCES += \
    resource.qrc
