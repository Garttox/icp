#include "editcalldialog.h"
#include "ui_editcalldialog.h"

#include <QPushButton>

#include <command/commandstack.h>

#include <command/sequence/editcallcommand.h>

EditCallDialog::EditCallDialog(UMLCallModel *umlCallModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCallDialog),
    umlCallModel(umlCallModel)
{
    ui->setupUi(this);

    ui->sourceComboBox->addItem(umlCallModel->getSource()->getDisplayName());
    ui->sourceComboBox->setEnabled(false);

    ui->destinationComboBox->addItem(umlCallModel->getDestination()->getDisplayName());
    ui->destinationComboBox->setEnabled(false);

    QList<UMLMethodModel*> umlMethodModels = umlCallModel->getDestination()->getClassModel()->getMethods();
    foreach (auto *umlMethodModel, umlMethodModels)
    {
        ui->methodComboBox->addItem(umlMethodModel->getName(), QVariant::fromValue(umlMethodModel));
    }

    int currentIndex = ui->methodComboBox->findData(QVariant::fromValue(umlCallModel->getMethod()));
    if (currentIndex != -1) {
        ui->methodComboBox->setCurrentIndex(currentIndex);
    }

    if (ui->methodComboBox->count() == 0)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }

    ui->asyncCheckBox->setChecked(umlCallModel->getAsync());

    ui->durationHorizontalSlider->setValue(umlCallModel->getDuration());
}

EditCallDialog::~EditCallDialog()
{
    delete ui;
}

void EditCallDialog::on_buttonBox_accepted()
{
    int duration = ui->durationHorizontalSlider->value();
    UMLMethodModel *method = ui->methodComboBox->currentData().value<UMLMethodModel *>();
    bool async = ui->asyncCheckBox->checkState() == Qt::Checked;
    CommandStack::getInstance().push(new EditCallCommand(umlCallModel, method, async, duration));
}

