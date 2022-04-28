#include <QDebug>
#include "newclassdialog.h"
#include "model/umlmethoddata.h"
#include "model/umlfielddata.h"
#include "model/umlaccesstype.h"
#include "model/dataprovider.h"
#include "model/umldata.h"
#include "model/umlclassdata.h"
#include "view/classes/editfielddialog.h"
#include "view/classes/editmethoddialog.h"
#include "ui_newclassdialog.h"
#include "ui_editfielddialog.h"
#include "ui_editmethoddialog.h"

NewClassDialog::NewClassDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClassDialog),
    umlClassData(new UMLClassData(QString(), UMLClassType::CLASS, DEFAULT_CLASS_POS_X, DEFAULT_CLASS_POS_Y))
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

NewClassDialog::~NewClassDialog()
{
    delete ui;
}

void NewClassDialog::on_buttonBox_accepted()
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    QString className = ui->nameLineEdit->text();
    umlClassData->setName(className);
    umlData->addClass(umlClassData);
}

void NewClassDialog::on_buttonBox_rejected()
{
    delete umlClassData;
}

void NewClassDialog::on_nameLineEdit_textEdited(const QString &text)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}

// Fields control buttons

void NewClassDialog::on_addFieldButton_clicked()
{
    UMLAccessType umlAccessType(UMLAccessType::PUBLIC);
    UMLFieldData *umlFieldData = new UMLFieldData(QString("New field"), QString("void"), umlAccessType);
    umlClassData->addField(umlFieldData);
    ui->fieldsList->addItem(umlFieldData->toString());
}

void NewClassDialog::on_editFieldButton_clicked()
{
    QModelIndexList selectedItems = ui->fieldsList->selectionModel()->selectedIndexes();
    foreach (auto selectedItem, selectedItems)
    {
        int selectedRow = selectedItem.row();
        UMLFieldData *umlFieldData = umlClassData->getFieldAt(selectedRow);
        EditFieldDialog *editFieldDialog = new EditFieldDialog(umlFieldData);
        editFieldDialog->exec();
        ui->fieldsList->takeItem(selectedRow);
        ui->fieldsList->insertItem(selectedRow, umlFieldData->toString());
    }
}

void NewClassDialog::on_removeFieldButton_clicked()
{
    QModelIndexList selectedIndexes = ui->fieldsList->selectionModel()->selectedIndexes();
    foreach (auto selectedIndex, selectedIndexes)
    {
        umlClassData->removeFieldAt(selectedIndex.row());
    }
    qDeleteAll(ui->fieldsList->selectedItems());
}


// Methods control buttons

void NewClassDialog::on_addMethodButton_clicked()
{
    UMLAccessType umlAccessType(UMLAccessType::PUBLIC);
    UMLMethodData *umlMethodData = new UMLMethodData(QString("New method"), QString("void"), umlAccessType);
    umlClassData->addMethod(umlMethodData);
    ui->methodsList->addItem(umlMethodData->toString());
}

void NewClassDialog::on_editMethodButton_clicked()
{
    QModelIndexList selectedItems = ui->methodsList->selectionModel()->selectedIndexes();
    foreach (auto selectedItem, selectedItems)
    {
        int selectedRow = selectedItem.row();
        UMLMethodData *umlMethodData = umlClassData->getMethodAt(selectedRow);
        EditMethodDialog *editFieldDialog = new EditMethodDialog(umlMethodData);
        editFieldDialog->exec();
        ui->methodsList->takeItem(selectedRow);
        ui->methodsList->insertItem(selectedRow, umlMethodData->toString());
    }
}

void NewClassDialog::on_removeMethodButton_clicked()
{
    QModelIndexList selectedIndexes = ui->methodsList->selectionModel()->selectedIndexes();
    foreach (auto selectedIndex, selectedIndexes)
    {
        umlClassData->removeMethodAt(selectedIndex.row());
    }
    qDeleteAll(ui->methodsList->selectedItems());
}

void NewClassDialog::on_fieldsList_itemSelectionChanged()
{
    bool hasSelectedItems = !ui->fieldsList->selectedItems().empty();
    ui->editFieldButton->setEnabled(hasSelectedItems);
    ui->removeFieldButton->setEnabled(hasSelectedItems);
}

void NewClassDialog::on_methodsList_itemSelectionChanged()
{
    bool hasSelectedItems = !ui->methodsList->selectedItems().empty();
    ui->editMethodButton->setEnabled(hasSelectedItems);
    ui->removeMethodButton->setEnabled(hasSelectedItems);
}

