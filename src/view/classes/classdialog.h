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
#include "model/umlclassmodel.h"
#include "model/umlfieldmodel.h"
#include "model/umlmethodmodel.h"
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
    void addField(UMLClassModel *umlClassModel, QListWidget *fieldsList);
    void addMethod(UMLClassModel *umlClassModel, QListWidget *methodsList);
    void editSelectedFields(UMLClassModel *umlClassModel, QListWidget *fieldsList);
    void editSelectedMethods(UMLClassModel *umlClassModel, QListWidget *methodsList);
    void removeSelectedFields(UMLClassModel *umlClassModel, QListWidget *fieldsList);
    void removeSelectedMethods(UMLClassModel *umlClassModel, QListWidget *methodsList);
    void disableButtonsIfListEmpty(QListWidget *list, QPushButton *btn1, QPushButton *btn2);
};

#endif // CLASSDIALOG_H
