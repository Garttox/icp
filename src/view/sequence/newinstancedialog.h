#ifndef NEWINSTANCEDIALOG_H
#define NEWINSTANCEDIALOG_H

#include <QDialog>

#include <model/umlsequencedata.h>

namespace Ui {
class NewInstanceDialog;
}

class NewInstanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewInstanceDialog(UMLSequenceData *umlSequenceData, QWidget *parent = nullptr);
    ~NewInstanceDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewInstanceDialog *ui;
    UMLSequenceData *umlSequenceData;
};

#endif // NEWINSTANCEDIALOG_H
