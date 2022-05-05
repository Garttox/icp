#include "newsequencedialog.h"
#include "ui_newsequencedialog.h"

#include <model/dataprovider.h>
#include <model/umlsequencedata.h>

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
    UMLSequenceData *umlSequenceData = new UMLSequenceData(name);
    DataProvider::getInstance().getUMLData()->addSequence(umlSequenceData);
}
