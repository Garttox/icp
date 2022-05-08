/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file newsequencedialog.cpp
 * @author Michal Trlica (xtrlic02)
 */
#include "newsequencedialog.h"
#include "ui_newsequencedialog.h"

#include <model/modelprovider.h>
#include <model/umlsequencemodel.h>

#include <QPushButton>

#include <command/commandstack.h>

#include <command/sequence/addsequencecommand.h>

NewSequenceDialog::NewSequenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSequenceDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

NewSequenceDialog::~NewSequenceDialog()
{
    delete ui;
}

void NewSequenceDialog::on_buttonBox_accepted()
{
    QString name = this->ui->nameLineEdit->text();
    UMLSequenceModel *umlSequenceModel = new UMLSequenceModel(name);
    CommandStack::getInstance().push(new AddSequenceCommand(umlSequenceModel));
}

void NewSequenceDialog::on_nameLineEdit_textEdited(const QString &text)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(text.isEmpty());
}

