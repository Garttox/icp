#ifndef NEWCLASSDIALOG_H
#define NEWCLASSDIALOG_H

#include <QDialog>
#include "model\umlclassdata.h"

namespace Ui {
class NewClassDialog;
}

class NewClassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewClassDialog(QWidget *parent = nullptr);
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

private:
    Ui::NewClassDialog *ui;
    UMLClassData *umlClassData;
    const int DEFAULT_CLASS_POS_X = 20;
    const int DEFAULT_CLASS_POS_Y = 20;
};

#endif // NEWCLASSDIALOG_H
