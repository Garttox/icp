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
        model/umlclasstype.cpp \
        model/umldata.cpp \
        model/umlfielddata.cpp \
        model/umlidentifier.cpp \
        model/umlmethoddata.cpp \
        model/umlmethodparameterdata.cpp \
        model/umlrelationdata.cpp \
        model/umlrelationtype.cpp \
        view/classdiagramview.cpp \
        view/classes/classdialog.cpp \
        view/classes/editclassdialog.cpp \
        view/classes/editfielddialog.cpp \
        view/classes/editmethoddialog.cpp \
        view/classes/editrelationdialog.cpp \
        view/classes/newclassdialog.cpp \
        view/classes/umlclass.cpp \
        view/classes/umlclassnotifier.cpp \
        view/classes/umlrelation.cpp \
        view/classes/umlrelationanchor.cpp \
        view/classtoolbar.cpp

HEADERS  += app.h \
    model/dataprovider.h \
    model/umlaccesstype.h \
    model/umlclassdata.h \
    model/umlclasstype.h \
    model/umldata.h \
    model/umlfielddata.h \
    model/umlidentifier.h \
    model/umlmethoddata.h \
    model/umlmethodparameterdata.h \
    model/umlrelationdata.h \
    model/umlrelationtype.h \
    view/classdiagramview.h \
    view/classes/classdialog.h \
    view/classes/editclassdialog.h \
    view/classes/editfielddialog.h \
    view/classes/editmethoddialog.h \
    view/classes/editrelationdialog.h \
    view/classes/newclassdialog.h \
    view/classes/umlclass.h \
    view/classes/umlclassnotifier.h \
    view/classes/umlrelation.h \
    view/classes/umlrelationanchor.h \
    view/classtoolbar.h

FORMS    += \
    view/classes/editclassdialog.ui \
    view/classes/editfielddialog.ui \
    view/classes/editmethoddialog.ui \
    view/classes/editrelationdialog.ui \
    view/classes/newclassdialog.ui

CONFIG += c++17

DISTFILES +=
