#ifndef EDITRELATIONDIALOG_H
#define EDITRELATIONDIALOG_H

#include "model/umlrelationdata.h"
#include <QDialog>

namespace Ui {
class EditRelationDialog;
}

class EditRelationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditRelationDialog(UMLRelationData *umlRelationData, QWidget *parent = nullptr);
    ~EditRelationDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditRelationDialog *ui;
    UMLRelationData *umlRelationData;
};

#endif // EDITRELATIONDIALOG_H
