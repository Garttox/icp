/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file editrelationdialog.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef EDITRELATIONDIALOG_H
#define EDITRELATIONDIALOG_H

#include "model/umlrelationmodel.h"
#include <QDialog>

namespace Ui {
class EditRelationDialog;
}

/**
 * @brief Dialog for editing relations. 
 * @author Martin Bednář (xbedna77)
 */
class EditRelationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditRelationDialog(UMLRelationModel *umlRelationModel, QWidget *parent = nullptr);
    ~EditRelationDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditRelationDialog *ui;
    UMLRelationModel *umlRelationModel;
};

#endif // EDITRELATIONDIALOG_H
