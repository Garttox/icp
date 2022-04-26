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
        view/classes/editfielddialog.cpp \
        view/classes/newclassdialog.cpp \
        view/classes/umlclass.cpp \
        view/diagramgraphicsview.cpp

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
    view/classes/editfielddialog.h \
    view/classes/newclassdialog.h \
    view/classes/umlclass.h \
    view/diagramgraphicsview.h

FORMS    += \
    view/classes/editfielddialog.ui \
    view/classes/newclassdialog.ui

CONFIG += c++17
