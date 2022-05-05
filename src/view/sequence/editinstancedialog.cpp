#include "editinstancedialog.h"
#include "ui_editinstancedialog.h"

EditInstanceDialog::EditInstanceDialog(UMLInstanceData *umlInstanceData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditInstanceDialog)
{
    ui->setupUi(this);

    ui->lineEdit->setText(umlInstanceData->getName());
    ui->comboBox->addItem(umlInstanceData->getClassData()->getName());
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox->setEnabled(false);
}

EditInstanceDialog::~EditInstanceDialog()
{
    delete ui;
}

void EditInstanceDialog::on_buttonBox_accepted()
{
    umlInstanceData->setName(ui->lineEdit->text());
}

