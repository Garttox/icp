/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file classdialog.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "classdialog.h"
#include "ui_editfielddialog.h"
#include "ui_editmethoddialog.h"

ClassDialog::ClassDialog()
{}

void ClassDialog::addField(UMLClassData *umlClassData, QListWidget *fieldsList)
{
    UMLAccessType umlAccessType(UMLAccessType::PUBLIC);
    UMLFieldData *umlFieldData = new UMLFieldData(QString("NewField"), QString("void"), umlAccessType);
    umlClassData->addField(umlFieldData);
    fieldsList->addItem(umlFieldData->toString());
}

void ClassDialog::addMethod(UMLClassData *umlClassData, QListWidget *methodsList)
{
    UMLAccessType umlAccessType(UMLAccessType::PUBLIC);
    UMLMethodData *umlMethodData = new UMLMethodData(QString("NewMethod"), QString("void"), umlAccessType);
    umlClassData->addMethod(umlMethodData);
    methodsList->addItem(umlMethodData->toString());
}

void ClassDialog::editSelectedFields(UMLClassData *umlClassData, QListWidget *fieldsList)
{
    QModelIndexList selectedItems = fieldsList->selectionModel()->selectedIndexes();
    foreach (auto selectedItem, selectedItems)
    {
        int selectedRow = selectedItem.row();
        UMLFieldData *umlFieldData = umlClassData->getFieldAt(selectedRow);
        EditFieldDialog *editFieldDialog = new EditFieldDialog(umlClassData->getType(), umlFieldData);
        editFieldDialog->exec();
        fieldsList->takeItem(selectedRow);
        fieldsList->insertItem(selectedRow, umlFieldData->toString());
    }
}

void ClassDialog::editSelectedMethods(UMLClassData *umlClassData, QListWidget *methodsList)
{

    QModelIndexList selectedItems = methodsList->selectionModel()->selectedIndexes();
    foreach (auto selectedItem, selectedItems)
    {
        int selectedRow = selectedItem.row();
        UMLMethodData *umlMethodData = umlClassData->getMethodAt(selectedRow);
        EditMethodDialog *editFieldDialog = new EditMethodDialog(umlClassData->getType(), umlMethodData);
        editFieldDialog->exec();
        methodsList->takeItem(selectedRow);
        methodsList->insertItem(selectedRow, umlMethodData->toString());
    }
}

void ClassDialog::removeSelectedFields(UMLClassData *umlClassData, QListWidget *fieldsList)
{
    QModelIndexList selectedIndexes = fieldsList->selectionModel()->selectedIndexes();
    for (auto i = selectedIndexes.rbegin(); i != selectedIndexes.rend(); ++i)
    {
        umlClassData->removeFieldAt(i->row());
    }
    qDeleteAll(fieldsList->selectedItems());
}

void ClassDialog::removeSelectedMethods(UMLClassData *umlClassData, QListWidget *methodsList)
{
    QModelIndexList selectedIndexes = methodsList->selectionModel()->selectedIndexes();
    for (auto i = selectedIndexes.rbegin(); i != selectedIndexes.rend(); ++i)
    {
        umlClassData->removeMethodAt(i->row());
    }
    qDeleteAll(methodsList->selectedItems());
}

void ClassDialog::disableButtonsIfListEmpty(QListWidget *list, QPushButton *btn1, QPushButton *btn2)
{
    bool hasSelectedItems = !list->selectedItems().empty();
    btn1->setEnabled(hasSelectedItems);
    btn2->setEnabled(hasSelectedItems);
}
