/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file editmethoddialog.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "editmethoddialog.h"
#include "ui_editmethoddialog.h"

EditMethodDialog::EditMethodDialog(UMLClassType classType, UMLMethodData *umlMethodData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMethodDialog),
    umlMethodData(umlMethodData)
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(umlMethodData->getName());
    ui->typeLineEdit->setText(umlMethodData->getType());
    ui->accessComboBox->addItems(UMLAccessType::asStringListFor(classType));
    ui->accessComboBox->setCurrentText(umlMethodData->getAccess().toString());
    ui->parametersTable->clearContents();
    setDataToParameterTable(umlMethodData);
}

EditMethodDialog::~EditMethodDialog()
{
    delete ui;
}


void EditMethodDialog::on_buttonBox_accepted()
{
    umlMethodData->setName(ui->nameLineEdit->text());
    umlMethodData->setType(ui->typeLineEdit->text());
    umlMethodData->setAccess(UMLAccessType(ui->accessComboBox->currentText()));
    umlMethodData->clearParameters();
    setDataFromParameterTable();
}

void EditMethodDialog::setDataToParameterTable(UMLMethodData *umlMethodData)
{
    int row = 0;
    foreach(UMLMethodParameterData *parameter, umlMethodData->getParameters())
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
                UMLMethodParameterData* umlMethodParameterData = new UMLMethodParameterData(name, type);
                umlMethodData->addParameter(umlMethodParameterData);
            }
        }
    }
}

