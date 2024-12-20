/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file editclassdialog.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef EDITCLASSDIALOG_H
#define EDITCLASSDIALOG_H

#include <QDialog>
#include "classdialog.h"
#include "model/umlclassmodel.h"

namespace Ui {
class EditClassDialog;
}

/**
 * @brief Dialog for editing classes.
 * @author Martin Bednář (xbedna77)
 */
class EditClassDialog : public QDialog, public ClassDialog
{
    Q_OBJECT

public:
    explicit EditClassDialog(UMLClassModel *umlClassModel, QWidget *parent = nullptr);
    ~EditClassDialog();

private slots:
    void on_buttonBox_accepted();
    void on_addFieldButton_clicked();
    void on_nameLineEdit_textEdited(const QString &arg1);
    void on_removeFieldButton_clicked();
    void on_editFieldButton_clicked();
    void on_addMethodButton_clicked();
    void on_editMethodButton_clicked();
    void on_removeMethodButton_clicked();
    void on_buttonBox_rejected();
    void on_fieldsList_itemSelectionChanged();
    void on_methodsList_itemSelectionChanged();

private:
    QString getHeaderString() const;

    Ui::EditClassDialog *ui;
    UMLClassModel *umlClassModel;
    UMLClassModel *umlClassModelCopy;
};

#endif // EDITCLASSDIALOG_H
