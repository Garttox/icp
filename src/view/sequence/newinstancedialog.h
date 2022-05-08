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
