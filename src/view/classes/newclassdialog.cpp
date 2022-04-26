#include "newclassdialog.h"
#include "ui_newclassdialog.h"
#include "model/dataprovider.h"
#include "model/umldata.h"
#include "model/umlclassdata.h"

NewClassDialog::NewClassDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClassDialog)
{
    ui->setupUi(this);
}

NewClassDialog::~NewClassDialog()
{
    delete ui;
}

void NewClassDialog::on_buttonBox_accepted()
{
    // TODO: Create new
    qDebug("Hello world");
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    UMLClassData *umlClassData = new UMLClassData(QString("My class"), UMLClassType::CLASS, 20, 20);
    umlData->addClass(umlClassData);
}
