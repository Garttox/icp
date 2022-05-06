#ifndef UMLMETHODMODEL_H
#define UMLMETHODMODEL_H

#include <QVector>
#include <QObject>

#include "umlattribute.h"
#include "umlparametermodel.h"

class UMLMethodModel : public UMLAttribute
{
    Q_OBJECT
public:
    UMLMethodModel(QString name, QString type, UMLAccessType access);
    UMLMethodModel(const UMLMethodModel &original);
    ~UMLMethodModel();
    bool loadData(QJsonObject jsonMethodData);
    QJsonObject getSaveData();
    void addParameter(UMLParameterModel *parameter);
    QString toString() const override;
    QList<UMLParameterModel *> getParameters() const;
    void clearParameters();
public slots:
    void parameterModelChanged();
signals:
    void modelChanged(UMLMethodModel* umlMethodModel);
private:
    QList<UMLParameterModel *> parameters;
};

#endif // UMLMETHODMODEL_H
