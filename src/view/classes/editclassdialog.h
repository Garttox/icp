#ifndef EDITCLASSDIALOG_H
#define EDITCLASSDIALOG_H

#include <QDialog>
#include "classdialog.h"
#include "model\umlclassdata.h"

namespace Ui {
class EditClassDialog;
}

class EditClassDialog : public QDialog, public ClassDialog
{
    Q_OBJECT

public:
    explicit EditClassDialog(UMLClassData *umlClassData, QWidget *parent = nullptr);
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
    UMLClassData *umlClassData;
    UMLClassData *umlClassDataCopy;
};

#endif // EDITCLASSDIALOG_H
