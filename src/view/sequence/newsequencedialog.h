/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file newsequencedialog.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef NEWSEQUENCEDIALOG_H
#define NEWSEQUENCEDIALOG_H

#include <QDialog>

namespace Ui {
class NewSequenceDialog;
}

/**
 * @brief Dialog for creating new UML Sequence.
 * @author Michal Trlica (xtrlic02)
 */
class NewSequenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewSequenceDialog(QWidget *parent = nullptr);
    ~NewSequenceDialog();

private slots:
    void on_buttonBox_accepted();
    void on_nameLineEdit_textEdited(const QString &arg1);

private:
    Ui::NewSequenceDialog *ui;
};

#endif // NEWSEQUENCEDIALOG_H
