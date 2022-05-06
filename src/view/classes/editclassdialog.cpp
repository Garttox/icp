/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file editclassdialog.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "editclassdialog.h"
#include "model/modelprovider.h"
#include "model/umlmodel.h"
#include "model/umlclassmodel.h"
#include "ui_editclassdialog.h"
#include "command/commandstack.h"
#include "command/classes/editclasscommand.h"

EditClassDialog::EditClassDialog(UMLClassModel *umlClassModel, QWidget *parent) :
    QDialog(parent),
    ClassDialog(),
    ui(new Ui::EditClassDialog),
    umlClassModel(umlClassModel),
    umlClassModelCopy(new UMLClassModel(*umlClassModel))
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(umlClassModelCopy->getName());
    ui->header->setText(getHeaderString());
    setWindowTitle(getHeaderString());

    foreach (UMLFieldModel *field, umlClassModelCopy->getFields())
    {
         ui->fieldsList->addItem(field->toString());
    }
    foreach (UMLMethodModel *method, umlClassModelCopy->getMethods())
    {
         ui->methodsList->addItem(method->toString());
    }
}

EditClassDialog::~EditClassDialog()
{
    delete ui;
}

// - - - - - private slots - - - - -

void EditClassDialog::on_buttonBox_accepted()
{
    umlClassModelCopy->setName(ui->nameLineEdit->text());
    CommandStack::getInstance().push(new EditClassCommand(umlClassModel, umlClassModelCopy));
}

void EditClassDialog::on_buttonBox_rejected()
{
    delete umlClassModelCopy;
}

void EditClassDialog::on_nameLineEdit_textEdited(const QString &text)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}


// Fields control buttons

void EditClassDialog::on_addFieldButton_clicked()
{
    addField(umlClassModelCopy, ui->fieldsList);
}

void EditClassDialog::on_editFieldButton_clicked()
{
    editSelectedFields(umlClassModelCopy, ui->fieldsList);
}

void EditClassDialog::on_removeFieldButton_clicked()
{
    removeSelectedFields(umlClassModelCopy, ui->fieldsList);
}


// Methods control buttons

void EditClassDialog::on_addMethodButton_clicked()
{
    addMethod(umlClassModelCopy, ui->methodsList);
}

void EditClassDialog::on_editMethodButton_clicked()
{
    editSelectedMethods(umlClassModelCopy, ui->methodsList);
}

void EditClassDialog::on_removeMethodButton_clicked()
{
    removeSelectedMethods(umlClassModelCopy, ui->methodsList);
}

// Item selection event handlers

void EditClassDialog::on_fieldsList_itemSelectionChanged()
{
    disableButtonsIfListEmpty(ui->fieldsList, ui->editFieldButton, ui->removeFieldButton);
}

void EditClassDialog::on_methodsList_itemSelectionChanged()
{
    disableButtonsIfListEmpty(ui->methodsList, ui->editMethodButton, ui->removeMethodButton);
}


// - - - - - private - - - - -

QString EditClassDialog::getHeaderString() const
{
    return "Edit " + umlClassModel->getType().toString();
}
