#include "editclassdialog.h"
#include "model/umlmethoddata.h"
#include "model/umlfielddata.h"
#include "model/umlaccesstype.h"
#include "model/dataprovider.h"
#include "model/umldata.h"
#include "model/umlclassdata.h"
#include "view/classes/editfielddialog.h"
#include "view/classes/editmethoddialog.h"
#include "ui_editclassdialog.h"
#include "ui_editfielddialog.h"
#include "ui_editmethoddialog.h"

EditClassDialog::EditClassDialog(UMLClassData *umlClassData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditClassDialog),
    umlClassData(umlClassData),
    umlClassDataCopy(new UMLClassData(*umlClassData))
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(umlClassDataCopy->getName());

    foreach (UMLFieldData *field, umlClassDataCopy->getFields()) {
         ui->fieldsList->addItem(field->toString());
    }

    foreach (UMLMethodData *method, umlClassDataCopy->getMethods()) {
         ui->methodsList->addItem(method->toString());
    }
}

EditClassDialog::~EditClassDialog()
{
    delete ui;
}

void EditClassDialog::on_buttonBox_accepted()
{
    // TODO
    /*
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    QString className = ui->nameLineEdit->text();
    umlClassData->setName(className);
    umlData->addClass(umlClassData);
    */
    umlClassDataCopy->setName(ui->nameLineEdit->text());
    umlClassData->setData(*umlClassDataCopy);

}

void EditClassDialog::on_buttonBox_rejected()
{
    delete umlClassDataCopy;
}

void EditClassDialog::on_nameLineEdit_textEdited(const QString &text)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}

// Fields control buttons

void EditClassDialog::on_addFieldButton_clicked()
{
    UMLAccessType umlAccessType(UMLAccessType::PUBLIC);
    UMLFieldData *umlFieldData = new UMLFieldData(QString("New field"), QString("void"), umlAccessType);
    umlClassDataCopy->addField(umlFieldData);
    ui->fieldsList->addItem(umlFieldData->toString());
}

void EditClassDialog::on_editFieldButton_clicked()
{
    QModelIndexList selectedItems = ui->fieldsList->selectionModel()->selectedIndexes();
    foreach (auto selectedItem, selectedItems)
    {
        int selectedRow = selectedItem.row();
        UMLFieldData *umlFieldData = umlClassDataCopy->getFieldAt(selectedRow);
        EditFieldDialog *editFieldDialog = new EditFieldDialog(umlFieldData);
        editFieldDialog->exec();
        ui->fieldsList->takeItem(selectedRow);
        ui->fieldsList->insertItem(selectedRow, umlFieldData->toString());
    }
}

void EditClassDialog::on_removeFieldButton_clicked()
{
    QModelIndexList selectedIndexes = ui->fieldsList->selectionModel()->selectedIndexes();
    foreach (auto selectedIndex, selectedIndexes)
    {
        umlClassDataCopy->removeFieldAt(selectedIndex.row());
    }
    qDeleteAll(ui->fieldsList->selectedItems());
}


// Methods control buttons

void EditClassDialog::on_addMethodButton_clicked()
{
    UMLAccessType umlAccessType(UMLAccessType::PUBLIC);
    UMLMethodData *umlMethodData = new UMLMethodData(QString("New method"), QString("void"), umlAccessType);
    umlClassDataCopy->addMethod(umlMethodData);
    ui->methodsList->addItem(umlMethodData->toString());
}

void EditClassDialog::on_editMethodButton_clicked()
{
    QModelIndexList selectedItems = ui->methodsList->selectionModel()->selectedIndexes();
    foreach (auto selectedItem, selectedItems)
    {
        int selectedRow = selectedItem.row();
        UMLMethodData *umlMethodData = umlClassDataCopy->getMethodAt(selectedRow);
        EditMethodDialog *editFieldDialog = new EditMethodDialog(umlMethodData);
        editFieldDialog->exec();
        ui->methodsList->takeItem(selectedRow);
        ui->methodsList->insertItem(selectedRow, umlMethodData->toString());
    }
}

void EditClassDialog::on_removeMethodButton_clicked()
{
    QModelIndexList selectedIndexes = ui->methodsList->selectionModel()->selectedIndexes();
    foreach (auto selectedIndex, selectedIndexes)
    {
        umlClassDataCopy->removeMethodAt(selectedIndex.row());
    }
    qDeleteAll(ui->methodsList->selectedItems());
}