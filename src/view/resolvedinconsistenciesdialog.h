#ifndef RESOLVEDINCONSISTENCIESDIALOG_H
#define RESOLVEDINCONSISTENCIESDIALOG_H

#include <QDialog>

namespace Ui {
class ResolvedInconsistenciesDialog;
}

class ResolvedInconsistenciesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResolvedInconsistenciesDialog(QStringList resolved, QWidget *parent = nullptr);
    ~ResolvedInconsistenciesDialog();

private:
    Ui::ResolvedInconsistenciesDialog *ui;
};

#endif // RESOLVEDINCONSISTENCIESDIALOG_H
