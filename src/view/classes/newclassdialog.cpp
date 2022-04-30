#include <QDebug>
#include "newclassdialog.h"
#include "model/dataprovider.h"
#include "model/umldata.h"
#include "model/umlclassdata.h"
#include "ui_newclassdialog.h"


NewClassDialog::NewClassDialog(UMLClassType classType, QPoint position, QWidget *parent) :
    QDialog(parent),
    ClassDialog(),
    ui(new Ui::NewClassDialog),
    umlClassData(new UMLClassData(QString(), classType, position.x(), position.y()))
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->header->setText(getHeaderString());
    setWindowTitle(getHeaderString());
}

NewClassDialog::~NewClassDialog()
{
    delete ui;
}


// - - - - - private slots - - - - -

void NewClassDialog::on_buttonBox_accepted()
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    QString className = ui->nameLineEdit->text();
    umlClassData->setName(className);
    umlData->addClass(umlClassData);
}

void NewClassDialog::on_buttonBox_rejected()
{
    delete umlClassData;
}

void NewClassDialog::on_nameLineEdit_textEdited(const QString &text)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!text.isEmpty());
}


// Fields buttons events

void NewClassDialog::on_addFieldButton_clicked()
{
    addField(umlClassData, ui->fieldsList);
}

void NewClassDialog::on_editFieldButton_clicked()
{
    editSelectedFields(umlClassData, ui->fieldsList);
}

void NewClassDialog::on_removeFieldButton_clicked()
{
    removeSelectedFields(umlClassData, ui->fieldsList);
}


// Methods buttons events

void NewClassDialog::on_addMethodButton_clicked()
{
    addMethod(umlClassData, ui->methodsList);
}

void NewClassDialog::on_editMethodButton_clicked()
{
    editSelectedMethods(umlClassData, ui->methodsList);
}

void NewClassDialog::on_removeMethodButton_clicked()
{
    removeSelectedMethods(umlClassData, ui->methodsList);
}


// Lists events

void NewClassDialog::on_fieldsList_itemSelectionChanged()
{
    disableButtonsIfListEmpty(ui->fieldsList, ui->editFieldButton, ui->removeFieldButton);
}

void NewClassDialog::on_methodsList_itemSelectionChanged()
{
    disableButtonsIfListEmpty(ui->methodsList, ui->editMethodButton, ui->removeMethodButton);
}


// - - - - - private - - - - -

QString NewClassDialog::getHeaderString() const
{
    return "Create " + umlClassData->getType().toDisplayString();
}
