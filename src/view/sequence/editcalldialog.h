#ifndef EDITCALLDIALOG_H
#define EDITCALLDIALOG_H

#include <QDialog>

#include <model/umlcallmodel.h>

namespace Ui {
class EditCallDialog;
}

class EditCallDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditCallDialog(UMLCallModel *umlCallModel, QWidget *parent = nullptr);
    ~EditCallDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditCallDialog *ui;
    UMLCallModel *umlCallModel;
};

#endif // EDITCALLDIALOG_H
