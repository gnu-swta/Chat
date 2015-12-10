#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T03:19:24
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Soft_DEV
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mainpage.cpp \
    chatpage.cpp \
    chatcontextlistitem.cpp \
    chatcontectlistitem_s.cpp \
    api_http.cpp \
    loading.cpp \
    submit_manager.cpp \
    submit_form.cpp \
    report_manager.cpp \
    report_form.cpp \
    report_create.cpp \
    subjectreport.cpp \
    eachreport.cpp

HEADERS  += widget.h \
    mainpage.h \
    chatpage.h \
    classinfo.h \
    chatcontextlistitem.h \
    chatcontectlistitem_s.h \
    api_http.h \
    type.h \
    loading.h \
    submit_manager.h \
    submit_form.h \
    report_manager.h \
    report_form.h \
    report_create.h \
    subjectreport.h \
    eachreport.h

FORMS    += widget.ui \
    mainpage.ui \
    chatpage.ui \
    chatcontextlistitem.ui \
    chatcontectlistitem_s.ui \
    loading.ui \
    submit_manager.ui \
    submit_form.ui \
    report_manager.ui \
    report_form.ui \
    report_create.ui \
    subjectreport.ui \
    eachreport.ui

RESOURCES += \
    resource.qrc
