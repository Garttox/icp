#ifndef NEWCLASSDIALOG_H
#define NEWCLASSDIALOG_H

#include <QDialog>

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

private:
    Ui::NewClassDialog *ui;
};

#endif // NEWCLASSDIALOG_H
