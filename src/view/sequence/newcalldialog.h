#ifndef NEWCALLDIALOG_H
#define NEWCALLDIALOG_H

#include <QDialog>

#include <model/umlsequencemodel.h>

namespace Ui {
class NewCallDialog;
}

class NewCallDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCallDialog(UMLSequenceModel *umlSequenceModel, UMLInstanceModel* destination, int atTime, QWidget *parent = nullptr);
    ~NewCallDialog();

private slots:
    void on_messageButtonBox_accepted();

    void on_createButtonBox_accepted();

    void on_destroyButtonBox_accepted();

    void on_createNameLineEdit_textEdited(const QString &arg1);

    void on_messageButtonBox_rejected();

    void on_destroyButtonBox_rejected();

    void on_createButtonBox_rejected();

private:
    Ui::NewCallDialog *ui;
    UMLSequenceModel *umlSequenceModel;
    UMLInstanceModel* destination;
    int atTime;

    static constexpr int DEFAULT_DURATION = 50;
    void setupMessageTab();
    void setupCreateTab();
    void setupDestroyTab();
};

#endif // NEWCALLDIALOG_H