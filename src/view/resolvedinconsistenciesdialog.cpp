/**
 * ICP - UML Application
 * @date 6/5/2022
 * @file resolvedinconsistenciesdialog.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "resolvedinconsistenciesdialog.h"
#include "ui_resolvedinconsistenciesdialog.h"

ResolvedInconsistenciesDialog::ResolvedInconsistenciesDialog(QStringList resolved, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResolvedInconsistenciesDialog)
{
    ui->setupUi(this);
    ui->listWidget->addItems(resolved);
}

ResolvedInconsistenciesDialog::~ResolvedInconsistenciesDialog()
{
    delete ui;
}
