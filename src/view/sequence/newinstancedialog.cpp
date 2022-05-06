#include "newinstancedialog.h"
#include "ui_newinstancedialog.h"

#include <model/modelprovider.h>
#include <model/umlclassmodel.h>
#include <model/umlinstancemodel.h>

NewInstanceDialog::NewInstanceDialog(UMLSequenceModel *umlSequenceModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewInstanceDialog),
    umlSequenceModel(umlSequenceModel)
{
    ui->setupUi(this);
    UMLModel *umlModel = ModelProvider::getInstance().getModel();

    foreach (UMLClassModel *cls, umlModel->getClasses())
    {
        ui->comboBox->addItem(cls->getName(), QVariant::fromValue(cls));
    }
    //ui->comboBox->setCurrentIndex(0);
}

NewInstanceDialog::~NewInstanceDialog()
{
    delete ui;
}

void NewInstanceDialog::on_buttonBox_accepted()
{
    QString name = ui->lineEdit->text();
    UMLClassModel *umlClassModel = ui->comboBox->currentData().value<UMLClassModel *>();
    UMLInstanceModel * umlInstanceModel = new UMLInstanceModel(name, umlClassModel, 100);
    umlSequenceModel->addInstance(umlInstanceModel);
}

