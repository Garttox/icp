/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file editfielddialog.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "editfielddialog.h"
#include "ui_editfielddialog.h"
#include "model/umlaccesstype.h"

EditFieldDialog::EditFieldDialog(UMLClassType classType, UMLFieldModel *umlFieldModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditFieldDialog),
    umlFieldModel(umlFieldModel)
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(umlFieldModel->getName());
    ui->typeLineEdit->setText(umlFieldModel->getType());
    ui->accessComboBox->addItems(UMLAccessType::asStringListFor(classType));
    ui->accessComboBox->setCurrentText(umlFieldModel->getAccess().toString());
}

EditFieldDialog::~EditFieldDialog()
{
    delete ui;
}

void EditFieldDialog::on_buttonBox_accepted()
{
    umlFieldModel->setName(ui->nameLineEdit->text());
    umlFieldModel->setType(ui->typeLineEdit->text());
    umlFieldModel->setAccess(UMLAccessType(ui->accessComboBox->currentText()));
}

