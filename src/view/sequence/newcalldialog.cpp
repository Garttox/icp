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
    atTime(atTime),
    destination(destination)
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

void NewCallDialog::on_createNameLineEdit_textEdited(const QString &text)
{
    ui->createButtonBox->button(QDialogButtonBox::Ok)->setDisabled(text.isEmpty() || (ui->createClassesComboBox->count() == 0));
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
    ui->createSourceComboBox->addItem(destination->getDisplayName());
    ui->createSourceComboBox->setEnabled(false);

    UMLModel *umlModel = ModelProvider::getInstance().getModel();
    foreach (UMLClassModel *cls, umlModel->getClasses())
    {
        if (cls->getType() == UMLClassType::CLASS)
        {
            ui->createClassesComboBox->addItem(cls->getName(), QVariant::fromValue(cls));
        }
    }
    ui->createButtonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

void NewCallDialog::setupDestroyTab()
{
    ui->destroySourceComboBox->addItem("(external)", QVariant::fromValue(nullptr));
    foreach (UMLInstanceModel *UMLInstanceModel, umlSequenceModel->getInstances())
    {
        ui->destroySourceComboBox->addItem(UMLInstanceModel->getDisplayName(), QVariant::fromValue(UMLInstanceModel));
    }

    ui->destroyDestinationComboBox->addItem(destination->getDisplayName());
    ui->destroyDestinationComboBox->setEnabled(false);
}
