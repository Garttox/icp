/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file editmethoddialog.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "editmethoddialog.h"
#include "ui_editmethoddialog.h"

EditMethodDialog::EditMethodDialog(UMLClassType classType, UMLMethodModel *umlMethodModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMethodDialog),
    umlMethodModel(umlMethodModel)
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(umlMethodModel->getName());
    ui->typeLineEdit->setText(umlMethodModel->getType());
    ui->accessComboBox->addItems(UMLAccessType::asStringListFor(classType));
    ui->accessComboBox->setCurrentText(umlMethodModel->getAccess().toString());
    ui->parametersTable->clearContents();
    setDataToParameterTable(umlMethodModel);
}

EditMethodDialog::~EditMethodDialog()
{
    delete ui;
}


void EditMethodDialog::on_buttonBox_accepted()
{
    umlMethodModel->setName(ui->nameLineEdit->text());
    umlMethodModel->setType(ui->typeLineEdit->text());
    umlMethodModel->setAccess(UMLAccessType(ui->accessComboBox->currentText()));
    umlMethodModel->clearParameters();
    setDataFromParameterTable();
}

void EditMethodDialog::setDataToParameterTable(UMLMethodModel *umlMethodModel)
{
    int row = 0;
    foreach(UMLParameterModel *parameter, umlMethodModel->getParameters())
    {
        QString name = parameter->getName();
        QString type = parameter->getType();
        ui->parametersTable->setItem(row, NAME_COLUMN_INDEX, new QTableWidgetItem(name));
        ui->parametersTable->setItem(row, TYPE_COLUMN_INDEX, new QTableWidgetItem(type));
        row++;
    }
}

void EditMethodDialog::setDataFromParameterTable()
{
    QTableWidget *table = ui->parametersTable;
    for(int row = 0; row < table->rowCount() - 1; row++)
    {
        QTableWidgetItem* nameItem = table->item(row, NAME_COLUMN_INDEX);
        QTableWidgetItem* typeItem = table->item(row, TYPE_COLUMN_INDEX);
        if (nameItem != nullptr)
        {
            QString name = nameItem->text();
            if (!name.isEmpty())
            {
                QString type = typeItem != nullptr ? typeItem->text() : QString("void");
                UMLParameterModel* umlMethodParameterModel = new UMLParameterModel(name, type);
                umlMethodModel->addParameter(umlMethodParameterModel);
            }
        }
    }
}

