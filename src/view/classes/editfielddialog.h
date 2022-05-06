/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file editfielddialog.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef EDITFIELDDIALOG_H
#define EDITFIELDDIALOG_H

#include <QDialog>
#include "model/umlfieldmodel.h"

namespace Ui {
class EditFieldDialog;
}

/**
 * @brief Dialog for editing fields.
 * @author Martin Bednář (xbedna77)
 */
class EditFieldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditFieldDialog(UMLClassType classType, UMLFieldModel *umlFieldModel, QWidget *parent = nullptr);
    ~EditFieldDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditFieldDialog *ui;
    UMLFieldModel *umlFieldModel;
};

#endif // EDITFIELDDIALOG_H
