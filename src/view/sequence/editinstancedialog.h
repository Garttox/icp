/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file editinstancedialog.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef EDITINSTANCEDIALOG_H
#define EDITINSTANCEDIALOG_H

#include <QDialog>

#include <model/umlinstancemodel.h>

namespace Ui {
class EditInstanceDialog;
}

/**
 * @brief Dialog for editing UML Instance.
 * @author Michal Trlica (xtrlic02)
 */
class EditInstanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditInstanceDialog(UMLInstanceModel *umlInstanceModel, QWidget *parent = nullptr);
    ~EditInstanceDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditInstanceDialog *ui;
    UMLInstanceModel *umlInstanceModel;
};

#endif // EDITINSTANCEDIALOG_H
