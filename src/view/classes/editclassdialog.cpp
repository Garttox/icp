#include "editclassdialog.h"
#include "model/dataprovider.h"
#include "model/umldata.h"
#include "model/umlclassdata.h"
#include "ui_editclassdialog.h"


EditClassDialog::EditClassDialog(UMLClassData *umlClassData, QWidget *parent) :
    QDialog(parent),
    ClassDialog(),
    ui(new Ui::EditClassDialog),
    umlClassData(umlClassData),
    umlClassDataCopy(new UMLClassData(*umlClassData))
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(umlClassDataCopy->getName());
    ui->header->setText(getHeaderString());
    setWindowTitle(getHeaderString());

    foreach (UMLFieldData *field, umlClassDataCopy->getFields())
    {
         ui->fieldsList->addItem(field->toString());
    }
    foreach (UMLMethodData *method, umlClassDataCopy->getMethods())
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
    addField(umlClassDataCopy, ui->fieldsList);
}

void EditClassDialog::on_editFieldButton_clicked()
{
    editSelectedFields(umlClassDataCopy, ui->fieldsList);
}

void EditClassDialog::on_removeFieldButton_clicked()
{
    removeSelectedFields(umlClassDataCopy, ui->fieldsList);
}


// Methods control buttons

void EditClassDialog::on_addMethodButton_clicked()
{
    addMethod(umlClassDataCopy, ui->methodsList);
}

void EditClassDialog::on_editMethodButton_clicked()
{
    editSelectedMethods(umlClassDataCopy, ui->methodsList);
}

void EditClassDialog::on_removeMethodButton_clicked()
{
    removeSelectedMethods(umlClassDataCopy, ui->methodsList);
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
    return "Edit " + umlClassData->getType().toDisplayString();
}
