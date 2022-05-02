/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file editmethoddialog.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef EDITMETHODDIALOG_H
#define EDITMETHODDIALOG_H

#include <QDialog>
#include "model/umlmethoddata.h"

namespace Ui {
class EditMethodDialog;
}

/**
 * @brief Dialog for editing methods. 
 * @author Martin Bednář (xbedna77)
 */
class EditMethodDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditMethodDialog(UMLClassType classType, UMLMethodData *umlMethodData, QWidget *parent = nullptr);
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
