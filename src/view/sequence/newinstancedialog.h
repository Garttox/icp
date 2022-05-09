/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file newinstancedialog.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef NEWINSTANCEDIALOG_H
#define NEWINSTANCEDIALOG_H

#include <QDialog>

#include <model/umlsequencemodel.h>

namespace Ui {
class NewInstanceDialog;
}

/**
 * @brief Dialog for creating new UML Instance.
 * @author Michal Trlica (xtrlic02)
 */
class NewInstanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewInstanceDialog(UMLSequenceModel *umlSequenceModel, int posX, QWidget *parent = nullptr);
    ~NewInstanceDialog();

private slots:
    void on_buttonBox_accepted();

    void on_nameLineEdit_textEdited(const QString &arg1);

private:
    Ui::NewInstanceDialog *ui;
    UMLSequenceModel *umlSequenceModel;
    int posX;
};

#endif // NEWINSTANCEDIALOG_H
