/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file classdialog.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef CLASSDIALOG_H
#define CLASSDIALOG_H

#include <QListWidget>
#include <QPushButton>
#include "editfielddialog.h"
#include "editmethoddialog.h"
#include "model/umlclassdata.h"
#include "model/umlfielddata.h"
#include "model/umlmethoddata.h"
#include "model/umlaccesstype.h"

/**
 * @brief Base class for NewClassDialog and EditClassDialog, containing their common features.
 * @author Martin Bednář (xbedna77)
 */
class ClassDialog
{
public:
    ClassDialog();

protected:
    void addField(UMLClassData *umlClassData, QListWidget *fieldsList);
    void addMethod(UMLClassData *umlClassData, QListWidget *methodsList);
    void editSelectedFields(UMLClassData *umlClassData, QListWidget *fieldsList);
    void editSelectedMethods(UMLClassData *umlClassData, QListWidget *methodsList);
    void removeSelectedFields(UMLClassData *umlClassData, QListWidget *fieldsList);
    void removeSelectedMethods(UMLClassData *umlClassData, QListWidget *methodsList);
    void disableButtonsIfListEmpty(QListWidget *list, QPushButton *btn1, QPushButton *btn2);
};

#endif // CLASSDIALOG_H
