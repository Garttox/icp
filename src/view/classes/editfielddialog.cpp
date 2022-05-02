/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file editfielddialog.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "editfielddialog.h"
#include "ui_editfielddialog.h"
#include "model/umlaccesstype.h"

EditFieldDialog::EditFieldDialog(UMLClassType classType, UMLFieldData *umlFieldData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditFieldDialog),
    umlFieldData(umlFieldData)
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(umlFieldData->getName());
    ui->typeLineEdit->setText(umlFieldData->getType());
    ui->accessComboBox->addItems(UMLAccessType::asStringListFor(classType));
    ui->accessComboBox->setCurrentText(umlFieldData->getAccess().toString());
}

EditFieldDialog::~EditFieldDialog()
{
    delete ui;
}

void EditFieldDialog::on_buttonBox_accepted()
{
    umlFieldData->setName(ui->nameLineEdit->text());
    umlFieldData->setType(ui->typeLineEdit->text());
    umlFieldData->setAccess(UMLAccessType(ui->accessComboBox->currentText()));
}

