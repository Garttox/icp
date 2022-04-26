#include "editfielddialog.h"
#include "ui_editfielddialog.h"
#include "model\umlaccesstype.h"

EditFieldDialog::EditFieldDialog(UMLFieldData *umlFieldData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditFieldDialog),
    umlFieldData(umlFieldData)
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(umlFieldData->getName());
    ui->typeLineEdit->setText(umlFieldData->getType());
    ui->accessComboBox->addItems(UMLAccessType::asStringList());
    ui->accessComboBox->setCurrentText(umlFieldData->getAccess()->toDisplayString());
}

EditFieldDialog::~EditFieldDialog()
{
    delete ui;
}

void EditFieldDialog::on_buttonBox_accepted()
{
    umlFieldData->setName(ui->nameLineEdit->text());
    umlFieldData->setType(ui->typeLineEdit->text());
    umlFieldData->setAccess(new UMLAccessType(ui->accessComboBox->currentText()));
}

