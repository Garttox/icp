/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file newcalldialog.cpp
 * @author Michal Trlica (xtrlic02)
 */
#include "newcalldialog.h"
#include "ui_newcalldialog.h"

#include <model/modelprovider.h>
#include <model/umlmodel.h>
#include <command/commandstack.h>
#include <command/sequence/addcallcommand.h>

#include <QPushButton>

NewCallDialog::NewCallDialog(UMLSequenceModel *umlSequenceModel, UMLInstanceModel* destination, int atTime, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCallDialog),
    umlSequenceModel(umlSequenceModel),
    destination(destination),
    atTime(atTime)
{
    ui->setupUi(this);

    setupMessageTab();
    setupCreateTab();
    setupDestroyTab();
}

NewCallDialog::~NewCallDialog()
{
    delete ui;
}

// - - - - - private slots - - - - -


void NewCallDialog::on_messageButtonBox_accepted()
{
    //UMLCallModel(UMLInstanceModel *source, UMLInstanceModel *destination, UMLMethodModel *method, bool async, int duration, int atTime, UMLCallType type);
    UMLInstanceModel* source = ui->messageSourceComboBox->currentData().value<UMLInstanceModel *>();
    UMLMethodModel* method = ui->messageMethodComboBox->currentData().value<UMLMethodModel *>();
    bool async = ui->messageAsyncCheckBox->checkState() == Qt::Checked;
    UMLCallModel *umlCallModel = new UMLCallModel(source, destination, method, async, DEFAULT_DURATION, atTime, UMLCallType::MESSAGE);
    CommandStack::getInstance().push(new AddCallCommand(umlSequenceModel, umlCallModel));
    close();
}

void NewCallDialog::on_messageButtonBox_rejected()
{
    close();
}

void NewCallDialog::on_createButtonBox_accepted()
{
    UMLInstanceModel* source = ui->createSourceComboBox->currentData().value<UMLInstanceModel *>();
    UMLCallModel *umlCallModel = new UMLCallModel(source, destination, nullptr, false, DEFAULT_DURATION, 0, UMLCallType::CREATE);
    CommandStack::getInstance().push(new AddCallCommand(umlSequenceModel, umlCallModel));
    close();
}

void NewCallDialog::on_createButtonBox_rejected()
{
    close();
}

void NewCallDialog::on_destroyButtonBox_accepted()
{
    UMLInstanceModel* source = ui->destroySourceComboBox->currentData().value<UMLInstanceModel *>();
    UMLCallModel *umlCallModel = new UMLCallModel(source, destination, nullptr, false, DEFAULT_DURATION, atTime, UMLCallType::DESTROY);
    CommandStack::getInstance().push(new AddCallCommand(umlSequenceModel, umlCallModel));
    close();
}

void NewCallDialog::on_destroyButtonBox_rejected()
{
    close();
}

// - - - - - private - - - - -

void NewCallDialog::setupMessageTab()
{
    ui->messageSourceComboBox->addItem("(external)", QVariant::fromValue(nullptr));
    foreach (UMLInstanceModel *UMLInstanceModel, umlSequenceModel->getInstances())
    {
        ui->messageSourceComboBox->addItem(UMLInstanceModel->getDisplayName(), QVariant::fromValue(UMLInstanceModel));
    }

    ui->messageDestinationComboBox->addItem(destination->getDisplayName());
    ui->messageDestinationComboBox->setEnabled(false);

    foreach (UMLMethodModel *umlMethodModel, destination->getClassModel()->getMethods())
    {
        ui->messageMethodComboBox->addItem(umlMethodModel->getName(), QVariant::fromValue(umlMethodModel));
    }

    if (ui->messageMethodComboBox->count() == 0)
    {
        ui->messageButtonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
}

void NewCallDialog::setupCreateTab()
{
    ui->createSourceComboBox->addItem("(external)", QVariant::fromValue(nullptr));
    foreach (UMLInstanceModel *UMLInstanceModel, umlSequenceModel->getInstances())
    {
        UMLCallModel *createCall = umlSequenceModel->instanceCreatedBy(UMLInstanceModel);
        if (!(createCall && createCall->getSource() && createCall->getSource() == destination)
                && UMLInstanceModel != destination)
        {
            ui->createSourceComboBox->addItem(UMLInstanceModel->getDisplayName(), QVariant::fromValue(UMLInstanceModel));
        }
    }

    ui->createDestinationComboBox->addItem(destination->getDisplayName());
    ui->createDestinationComboBox->setEnabled(false);

    if (umlSequenceModel->instanceCreatedBy(destination))
    {
        ui->createButtonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
}

void NewCallDialog::setupDestroyTab()
{
    ui->destroySourceComboBox->addItem("(external)", QVariant::fromValue(nullptr));
    foreach (UMLInstanceModel *UMLInstanceModel, umlSequenceModel->getInstances())
    {
        UMLCallModel *createCall = umlSequenceModel->instanceDestroyedBy(UMLInstanceModel);
        if (!(createCall && createCall->getSource() && createCall->getSource() == destination)
                && UMLInstanceModel != destination)
        {
            ui->destroySourceComboBox->addItem(UMLInstanceModel->getDisplayName(), QVariant::fromValue(UMLInstanceModel));
        }
    }

    ui->destroyDestinationComboBox->addItem(destination->getDisplayName());
    ui->destroyDestinationComboBox->setEnabled(false);

    if (umlSequenceModel->instanceDestroyedBy(destination))
    {
        ui->destroyButtonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
}
