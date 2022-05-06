#ifndef NEWINSTANCEDIALOG_H
#define NEWINSTANCEDIALOG_H

#include <QDialog>

#include <model/umlsequencemodel.h>

namespace Ui {
class NewInstanceDialog;
}

class NewInstanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewInstanceDialog(UMLSequenceModel *umlSequenceModel, QWidget *parent = nullptr);
    ~NewInstanceDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewInstanceDialog *ui;
    UMLSequenceModel *umlSequenceModel;
};

#endif // NEWINSTANCEDIALOG_H
