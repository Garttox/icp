#-------------------------------------------------
#
# Project created by QtCreator 2022-04-19T22:41:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = icp
TEMPLATE = app


SOURCES += main.cpp\
        app.cpp \
        model/dataprovider.cpp \
        model/umlaccesstype.cpp \
        model/umlclassdata.cpp \
        model/umldata.cpp \
        model/umlfielddata.cpp \
        model/umlidentifier.cpp \
        model/umlmethoddata.cpp \
        model/umlmethodparameterdata.cpp \
        model/umlrelationdata.cpp \
        model/umlrelationtype.cpp \
        view/classes/umlclass.cpp

HEADERS  += app.h \
    model/dataprovider.h \
    model/umlaccesstype.h \
    model/umlclassdata.h \
    model/umldata.h \
    model/umlfielddata.h \
    model/umlidentifier.h \
    model/umlmethoddata.h \
    model/umlmethodparameterdata.h \
    model/umlrelationdata.h \
    model/umlrelationtype.h \
    view/classes/umlclass.h

FORMS    +=

CONFIG += c++17
