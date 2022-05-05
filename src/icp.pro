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
        command/classes/addclasscommand.cpp \
        command/classes/addrelationcommand.cpp \
        command/classes/editclasscommand.cpp \
        command/classes/editrelationcommand.cpp \
        command/classes/moveclasscommand.cpp \
        command/command.cpp \
        command/commandstack.cpp \
        model/dataprovider.cpp \
        model/umlaccesstype.cpp \
        model/umlattribute.cpp \
        model/umlcalldata.cpp \
        model/umlcalltype.cpp \
        model/umlclassdata.cpp \
        model/umlclasstype.cpp \
        model/umldata.cpp \
        model/umlfielddata.cpp \
        model/umlinstancedata.cpp \
        model/umlmethoddata.cpp \
        model/umlmethodparameterdata.cpp \
        model/umlrelationdata.cpp \
        model/umlrelationtype.cpp \
        model/umlsequencedata.cpp \
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
        view/classtoolbar.cpp \
        view/sequence/editinstancedialog.cpp \
        view/sequence/newinstancedialog.cpp \
        view/sequence/newsequencedialog.cpp \
        view/sequence/umlinstance.cpp \
        view/sequence/umlinstancelifeline.cpp \
        view/sequencediagramview.cpp

HEADERS  += app.h \
    command/classes/addclasscommand.h \
    command/classes/addrelationcommand.h \
    command/classes/editclasscommand.h \
    command/classes/editrelationcommand.h \
    command/classes/moveclasscommand.h \
    command/command.h \
    command/commandstack.h \
    model/dataprovider.h \
    model/umlaccesstype.h \
    model/umlattribute.h \
    model/umlcalldata.h \
    model/umlcalltype.h \
    model/umlclassdata.h \
    model/umlclasstype.h \
    model/umldata.h \
    model/umlfielddata.h \
    model/umlinstancedata.h \
    model/umlmethoddata.h \
    model/umlmethodparameterdata.h \
    model/umlrelationdata.h \
    model/umlrelationtype.h \
    model/umlsequencedata.h \
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
    view/classtoolbar.h \
    view/sequence/editinstancedialog.h \
    view/sequence/newinstancedialog.h \
    view/sequence/newsequencedialog.h \
    view/sequence/umlinstance.h \
    view/sequence/umlinstancelifeline.h \
    view/sequencediagramview.h

FORMS    += \
    view/classes/editclassdialog.ui \
    view/classes/editfielddialog.ui \
    view/classes/editmethoddialog.ui \
    view/classes/editrelationdialog.ui \
    view/classes/newclassdialog.ui \
    view/sequence/editinstancedialog.ui \
    view/sequence/newinstancedialog.ui \
    view/sequence/newsequencedialog.ui

CONFIG += c++17

DISTFILES +=
