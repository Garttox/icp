#include "editrelationdialog.h"
#include "ui_editrelationdialog.h"
#include "model/umlrelationtype.h"

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
    umlRelationData->setType(type);
}

