/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file newclassdialog.h
 * @author Martin Bednář (xbedna77)
 */
#ifndef NEWCLASSDIALOG_H
#define NEWCLASSDIALOG_H

#include <QDialog>
#include "classdialog.h"
#include "model/umlclassmodel.h"

namespace Ui {
class NewClassDialog;
}

/**
 * @brief Dialog for creating new UML classes. 
 * @author Martin Bednář (xbedna77)
 */
class NewClassDialog : public QDialog, public ClassDialog
{
    Q_OBJECT

public:
    explicit NewClassDialog(UMLClassType classType, QPoint position, QWidget *parent = nullptr);
    ~NewClassDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_addFieldButton_clicked();
    void on_nameLineEdit_textEdited(const QString &arg1);
    void on_removeFieldButton_clicked();
    void on_editFieldButton_clicked();
    void on_addMethodButton_clicked();
    void on_editMethodButton_clicked();
    void on_removeMethodButton_clicked();
    void on_fieldsList_itemSelectionChanged();
    void on_methodsList_itemSelectionChanged();

private:
    QString getHeaderString() const;

    Ui::NewClassDialog *ui;
    UMLClassModel *umlClassModel;
};

#endif // NEWCLASSDIALOG_H
