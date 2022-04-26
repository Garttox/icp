#include "editfielddialog.h"
#include "ui_editfielddialog.h"

EditFieldDialog::EditFieldDialog(UMLFieldData *umlFieldData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditFieldDialog),
    umlFieldData(umlFieldData)
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(umlFieldData->getName());
    ui->typeLineEdit->setText(umlFieldData->getType());
    //  ui->accessComboBox->
}

EditFieldDialog::~EditFieldDialog()
{
    delete ui;
}
