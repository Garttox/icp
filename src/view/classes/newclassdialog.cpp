/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file newclassdialog.cpp
 * @author Martin Bednář (xbedna77)
 */

#include <QDebug>
#include "newclassdialog.h"
#include "model/modelprovider.h"
#include "model/umlmodel.h"
#include "model/umlclassmodel.h"
#include "ui_newclassdialog.h"
#include "command/commandstack.h"
#include "command/classes/addclasscommand.h"

NewClassDialog::NewClassDialog(UMLClassType classType, QPoint position, QWidget *parent) :
    QDialog(parent),
    ClassDialog(),
    ui(new Ui::NewClassDialog),
    umlClassModel(new UMLClassModel(QString(), classType, position.x(), position.y()))
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->header->setText(getHeaderString());
    setWindowTitle(getHeaderString());
}

NewClassDialog::~NewClassDialog()
{
    delete ui;
}


// - - - - - private slots - - - - -

void NewClassDialog::on_buttonBox_accepted()
{
    QString className = ui->nameLineEdit->text();
    umlClassModel->setName(className);
    CommandStack::getInstance().push(new AddClassCommand(umlClassModel));
}

void NewClassDialog::on_buttonBox_rejected()
{
    delete umlClassModel;
}

void NewClassDialog::on_nameLineEdit_textEdited(const QString &text)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}


// Fields buttons events

void NewClassDialog::on_addFieldButton_clicked()
{
    addField(umlClassModel, ui->fieldsList);
}

void NewClassDialog::on_editFieldButton_clicked()
{
    editSelectedFields(umlClassModel, ui->fieldsList);
}

void NewClassDialog::on_removeFieldButton_clicked()
{
    removeSelectedFields(umlClassModel, ui->fieldsList);
}


// Methods buttons events

void NewClassDialog::on_addMethodButton_clicked()
{
    addMethod(umlClassModel, ui->methodsList);
}

void NewClassDialog::on_editMethodButton_clicked()
{
    editSelectedMethods(umlClassModel, ui->methodsList);
}

void NewClassDialog::on_removeMethodButton_clicked()
{
    removeSelectedMethods(umlClassModel, ui->methodsList);
}


// Lists events

void NewClassDialog::on_fieldsList_itemSelectionChanged()
{
    disableButtonsIfListEmpty(ui->fieldsList, ui->editFieldButton, ui->removeFieldButton);
}

void NewClassDialog::on_methodsList_itemSelectionChanged()
{
    disableButtonsIfListEmpty(ui->methodsList, ui->editMethodButton, ui->removeMethodButton);
}


// - - - - - private - - - - -

QString NewClassDialog::getHeaderString() const
{
    return "Create " + umlClassModel->getType().toString();
}
