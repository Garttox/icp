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

void ClassDialog::addField(UMLClassModel *umlClassModel, QListWidget *fieldsList)
{
    UMLAccessType umlAccessType(UMLAccessType::PUBLIC);
    UMLFieldModel *umlFieldModel = new UMLFieldModel(QString("NewField"), QString("void"), umlAccessType);
    umlClassModel->addField(umlFieldModel);
    fieldsList->addItem(umlFieldModel->toString());
}

void ClassDialog::addMethod(UMLClassModel *umlClassModel, QListWidget *methodsList)
{
    UMLAccessType umlAccessType(UMLAccessType::PUBLIC);
    UMLMethodModel *umlMethodModel = new UMLMethodModel(QString("NewMethod"), QString("void"), umlAccessType);
    umlClassModel->addMethod(umlMethodModel);
    methodsList->addItem(umlMethodModel->toString());
}

void ClassDialog::editSelectedFields(UMLClassModel *umlClassModel, QListWidget *fieldsList)
{
    QModelIndexList selectedItems = fieldsList->selectionModel()->selectedIndexes();
    foreach (auto selectedItem, selectedItems)
    {
        int selectedRow = selectedItem.row();
        UMLFieldModel *umlFieldModel = umlClassModel->getFieldAt(selectedRow);
        EditFieldDialog *editFieldDialog = new EditFieldDialog(umlClassModel->getType(), umlFieldModel);
        editFieldDialog->exec();
        fieldsList->takeItem(selectedRow);
        fieldsList->insertItem(selectedRow, umlFieldModel->toString());
    }
}

void ClassDialog::editSelectedMethods(UMLClassModel *umlClassModel, QListWidget *methodsList)
{

    QModelIndexList selectedItems = methodsList->selectionModel()->selectedIndexes();
    foreach (auto selectedItem, selectedItems)
    {
        int selectedRow = selectedItem.row();
        UMLMethodModel *umlMethodModel = umlClassModel->getMethodAt(selectedRow);
        EditMethodDialog *editFieldDialog = new EditMethodDialog(umlClassModel->getType(), umlMethodModel);
        editFieldDialog->exec();
        methodsList->takeItem(selectedRow);
        methodsList->insertItem(selectedRow, umlMethodModel->toString());
    }
}

void ClassDialog::removeSelectedFields(UMLClassModel *umlClassModel, QListWidget *fieldsList)
{
    QModelIndexList selectedIndexes = fieldsList->selectionModel()->selectedIndexes();
    for (auto i = selectedIndexes.rbegin(); i != selectedIndexes.rend(); ++i)
    {
        umlClassModel->removeFieldAt(i->row());
    }
    qDeleteAll(fieldsList->selectedItems());
}

void ClassDialog::removeSelectedMethods(UMLClassModel *umlClassModel, QListWidget *methodsList)
{
    QModelIndexList selectedIndexes = methodsList->selectionModel()->selectedIndexes();
    for (auto i = selectedIndexes.rbegin(); i != selectedIndexes.rend(); ++i)
    {
        umlClassModel->removeMethodAt(i->row());
    }
    qDeleteAll(methodsList->selectedItems());
}

void ClassDialog::disableButtonsIfListEmpty(QListWidget *list, QPushButton *btn1, QPushButton *btn2)
{
    bool hasSelectedItems = !list->selectedItems().empty();
    btn1->setEnabled(hasSelectedItems);
    btn2->setEnabled(hasSelectedItems);
}
