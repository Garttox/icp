/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file editcalldialog.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef EDITCALLDIALOG_H
#define EDITCALLDIALOG_H

#include <QDialog>

#include <model/umlcallmodel.h>

namespace Ui {
class EditCallDialog;
}

/**
 * @brief Dialog for editing UML Call.
 * @author Michal Trlica (xtrlic02)
 */
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
