#include "newinstancedialog.h"
#include "ui_newinstancedialog.h"

#include <model/modelprovider.h>
#include <model/umlclassmodel.h>
#include <model/umlinstancemodel.h>
#include <command/commandstack.h>
#include <command/sequence/addinstancecommand.h>

#include <QPushButton>

NewInstanceDialog::NewInstanceDialog(UMLSequenceModel *umlSequenceModel, int posX, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewInstanceDialog),
    umlSequenceModel(umlSequenceModel), posX(posX)
{
    ui->setupUi(this);
    UMLModel *umlModel = ModelProvider::getInstance().getModel();

    foreach (UMLClassModel *cls, umlModel->getClasses())
    {
        if (cls->getType() == UMLClassType::CLASS)
        {
            ui->classesComboBox->addItem(cls->getName(), QVariant::fromValue(cls));
        }
    }

    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

NewInstanceDialog::~NewInstanceDialog()
{
    delete ui;
}

void NewInstanceDialog::on_buttonBox_accepted()
{
    QString name = ui->nameLineEdit->text();
    UMLClassModel *umlClassModel = ui->classesComboBox->currentData().value<UMLClassModel *>();
    UMLInstanceModel * umlInstanceModel = new UMLInstanceModel(name, umlClassModel, posX);
    CommandStack::getInstance().push(new AddInstanceCommand(umlSequenceModel, umlInstanceModel));
}


void NewInstanceDialog::on_nameLineEdit_textEdited(const QString &text)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(text.isEmpty() || (ui->classesComboBox->count() == 0));
}

