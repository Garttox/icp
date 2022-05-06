#include "newsequencedialog.h"
#include "ui_newsequencedialog.h"

#include <model/modelprovider.h>
#include <model/umlsequencemodel.h>

NewSequenceDialog::NewSequenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSequenceDialog)
{
    ui->setupUi(this);
}

NewSequenceDialog::~NewSequenceDialog()
{
    delete ui;
}

void NewSequenceDialog::on_buttonBox_accepted()
{
    QString name = this->ui->lineEdit->text();
    UMLSequenceModel *umlSequenceModel = new UMLSequenceModel(name);
    ModelProvider::getInstance().getModel()->addSequence(umlSequenceModel);
}
