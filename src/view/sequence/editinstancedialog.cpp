#include "editinstancedialog.h"
#include "ui_editinstancedialog.h"

#include <command/sequence/editinstancecommand.h>

#include <command/commandstack.h>

EditInstanceDialog::EditInstanceDialog(UMLInstanceModel *umlInstanceModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditInstanceDialog),
    umlInstanceModel(umlInstanceModel)
{
    ui->setupUi(this);

    ui->nameLineEdit->setText(umlInstanceModel->getName());
    ui->classComboBox->addItem(umlInstanceModel->getClassModel()->getName());
    ui->classComboBox->setCurrentIndex(0);
    ui->classComboBox->setEnabled(false);
}

EditInstanceDialog::~EditInstanceDialog()
{
    delete ui;
}

void EditInstanceDialog::on_buttonBox_accepted()
{
    CommandStack::getInstance().push(new EditInstanceCommand(umlInstanceModel, ui->nameLineEdit->text()));
}

