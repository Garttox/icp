#ifndef EDITINSTANCEDIALOG_H
#define EDITINSTANCEDIALOG_H

#include <QDialog>

#include <model/umlinstancedata.h>

namespace Ui {
class EditInstanceDialog;
}

class EditInstanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditInstanceDialog(UMLInstanceData *umlInstanceData, QWidget *parent = nullptr);
    ~EditInstanceDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditInstanceDialog *ui;
    UMLInstanceData *umlInstanceData;
};

#endif // EDITINSTANCEDIALOG_H
