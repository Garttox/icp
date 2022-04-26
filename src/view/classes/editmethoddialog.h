#ifndef EDITMETHODDIALOG_H
#define EDITMETHODDIALOG_H

#include <QDialog>
#include "model\umlmethoddata.h"

namespace Ui {
class EditMethodDialog;
}

class EditMethodDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditMethodDialog(UMLMethodData *umlMethodData, QWidget *parent = nullptr);
    ~EditMethodDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditMethodDialog *ui;
    UMLMethodData *umlMethodData;
    void setDataToParameterTable(UMLMethodData *umlMethodData);
    void setDataFromParameterTable();

    const int NAME_COLUMN_INDEX = 0;
    const int TYPE_COLUMN_INDEX = 1;
};

#endif // EDITMETHODDIALOG_H
