#include "newinstancedialog.h"
#include "ui_newinstancedialog.h"

#include <model/dataprovider.h>
#include <model/umlclassdata.h>
#include <model/umlinstancedata.h>

NewInstanceDialog::NewInstanceDialog(UMLSequenceData *umlSequenceData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewInstanceDialog),
    umlSequenceData(umlSequenceData)
{
    ui->setupUi(this);
    UMLData *umlData = DataProvider::getInstance().getUMLData();

    foreach (UMLClassData *cls, *umlData->getClasses())
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
    UMLClassData *umlClassData = ui->comboBox->currentData().value<UMLClassData *>();
    UMLInstanceData * umlInstanceData = new UMLInstanceData(name, umlClassData, 100);
    umlSequenceData->addInstance(umlInstanceData);
}

