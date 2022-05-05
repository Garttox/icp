/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file editrelationdialog.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "editrelationdialog.h"
#include "ui_editrelationdialog.h"
#include "model/umlrelationtype.h"
#include "command/commandstack.h"
#include "command/classes/editrelationcommand.h"

EditRelationDialog::EditRelationDialog(UMLRelationData *umlRelationData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditRelationDialog),
    umlRelationData(umlRelationData)
{
    ui->setupUi(this);

    ui->sourceLineEdit->setText(umlRelationData->getSource()->getDisplayName());
    ui->destinationLineEdit->setText(umlRelationData->getDestination()->getDisplayName());
    ui->typeComboBox->addItems(UMLRelationType::asStringList());
    ui->typeComboBox->setCurrentText(umlRelationData->getType().toString());
}

EditRelationDialog::~EditRelationDialog()
{
    delete ui;
}

void EditRelationDialog::on_buttonBox_accepted()
{
    UMLRelationType type(ui->typeComboBox->currentText());
    CommandStack::getInstance().push(new EditRelationCommand(umlRelationData, type));
}

