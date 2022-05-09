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
        command/sequence/addcallcommand.cpp \
        command/sequence/addinstancecommand.cpp \
        command/sequence/addsequencecommand.cpp \
        command/sequence/editcallcommand.cpp \
        command/sequence/editinstancecommand.cpp \
        command/sequence/movecallcommand.cpp \
        command/sequence/moveinstancecommand.cpp \
        data/inconsistencyresolver.cpp \
        data/umlattributedata.cpp \
        data/umlcalldata.cpp \
        data/umlclassdata.cpp \
        data/umldata.cpp \
        data/umlfielddata.cpp \
        data/umlinstancedata.cpp \
        data/umlmethoddata.cpp \
        data/umlparameterdata.cpp \
        data/umlrelationdata.cpp \
        data/umlsequencedata.cpp \
        model/modelprovider.cpp \
        model/umlaccesstype.cpp \
        model/umlattribute.cpp \
        model/umlcallmodel.cpp \
        model/umlcalltype.cpp \
        model/umlclassmodel.cpp \
        model/umlclasstype.cpp \
        model/umlfieldmodel.cpp \
        model/umlinstancemodel.cpp \
        model/umlmethodmodel.cpp \
        model/umlmodel.cpp \
        model/umlparametermodel.cpp \
        model/umlrelationmodel.cpp \
        model/umlrelationtype.cpp \
        model/umlsequencemodel.cpp \
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
        view/resolvedinconsistenciesdialog.cpp \
        view/sequence/editcalldialog.cpp \
        view/sequence/editinstancedialog.cpp \
        view/sequence/newcalldialog.cpp \
        view/sequence/newinstancedialog.cpp \
        view/sequence/newsequencedialog.cpp \
        view/sequence/umlcall.cpp \
        view/sequence/umlcallarrow.cpp \
        view/sequence/umlinstance.cpp \
        view/sequence/umlinstancelifeline.cpp \
        view/sequencediagramview.cpp \
        view/sequencetoolbar.cpp

HEADERS  += app.h \
    command/classes/addclasscommand.h \
    command/classes/addrelationcommand.h \
    command/classes/editclasscommand.h \
    command/classes/editrelationcommand.h \
    command/classes/moveclasscommand.h \
    command/command.h \
    command/commandstack.h \
    command/sequence/addcallcommand.h \
    command/sequence/addinstancecommand.h \
    command/sequence/addsequencecommand.h \
    command/sequence/editcallcommand.h \
    command/sequence/editinstancecommand.h \
    command/sequence/movecallcommand.h \
    command/sequence/moveinstancecommand.h \
    data/data.h \
    data/inconsistencyresolver.h \
    data/umlattributedata.h \
    data/umlcalldata.h \
    data/umlclassdata.h \
    data/umldata.h \
    data/umlfielddata.h \
    data/umlinstancedata.h \
    data/umlmethoddata.h \
    data/umlparameterdata.h \
    data/umlrelationdata.h \
    data/umlsequencedata.h \
    data/utils.h \
    model/modelprovider.h \
    model/umlaccesstype.h \
    model/umlattribute.h \
    model/umlcallmodel.h \
    model/umlcalltype.h \
    model/umlclassmodel.h \
    model/umlclasstype.h \
    model/umlfieldmodel.h \
    model/umlinstancemodel.h \
    model/umlmethodmodel.h \
    model/umlmodel.h \
    model/umlparametermodel.h \
    model/umlrelationmodel.h \
    model/umlrelationtype.h \
    model/umlsequencemodel.h \
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
    view/resolvedinconsistenciesdialog.h \
    view/sequence/editcalldialog.h \
    view/sequence/editinstancedialog.h \
    view/sequence/newcalldialog.h \
    view/sequence/newinstancedialog.h \
    view/sequence/newsequencedialog.h \
    view/sequence/umlcall.h \
    view/sequence/umlcallarrow.h \
    view/sequence/umlinstance.h \
    view/sequence/umlinstancelifeline.h \
    view/sequencediagramview.h \
    view/sequencetoolbar.h

FORMS    += \
    view/classes/editclassdialog.ui \
    view/classes/editfielddialog.ui \
    view/classes/editmethoddialog.ui \
    view/classes/editrelationdialog.ui \
    view/classes/newclassdialog.ui \
    view/resolvedinconsistenciesdialog.ui \
    view/sequence/editcalldialog.ui \
    view/sequence/editinstancedialog.ui \
    view/sequence/newcalldialog.ui \
    view/sequence/newinstancedialog.ui \
    view/sequence/newsequencedialog.ui

CONFIG += c++17

DISTFILES +=
