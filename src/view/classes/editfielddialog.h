#ifndef EDITFIELDDIALOG_H
#define EDITFIELDDIALOG_H

#include <QDialog>
#include "model\umlfielddata.h"

namespace Ui {
class EditFieldDialog;
}

class EditFieldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditFieldDialog(UMLFieldData *umlFieldData, QWidget *parent = nullptr);
    ~EditFieldDialog();

private:
    Ui::EditFieldDialog *ui;
    UMLFieldData *umlFieldData;
};

#endif // EDITFIELDDIALOG_H
