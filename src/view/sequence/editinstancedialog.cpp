#include "editinstancedialog.h"
#include "ui_editinstancedialog.h"

EditInstanceDialog::EditInstanceDialog(UMLInstanceModel *umlInstanceModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditInstanceDialog)
{
    ui->setupUi(this);

    ui->lineEdit->setText(umlInstanceModel->getName());
    ui->comboBox->addItem(umlInstanceModel->getClassModel()->getName());
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox->setEnabled(false);
}

EditInstanceDialog::~EditInstanceDialog()
{
    delete ui;
}

void EditInstanceDialog::on_buttonBox_accepted()
{
    umlInstanceModel->setName(ui->lineEdit->text());
}

