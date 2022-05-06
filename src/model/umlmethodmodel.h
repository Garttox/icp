#ifndef UMLMETHODMODEL_H
#define UMLMETHODMODEL_H

#include <QVector>
#include <QObject>

#include "umlattribute.h"
#include "umlmethodparametermodel.h"

class UMLMethodModel : public UMLAttribute
{
    Q_OBJECT
public:
    UMLMethodModel(QString name, QString type, UMLAccessType access);
    UMLMethodModel(const UMLMethodModel &original);
    ~UMLMethodModel();
    bool loadData(QJsonObject jsonMethodData);
    QJsonObject getSaveData();
    void addParameter(UMLMethodParameterModel *parameter);
    QString toString() const override;
    QList<UMLMethodParameterModel *> getParameters() const;
    void clearParameters();
public slots:
    void parameterModelChanged();
signals:
    void modelChanged(UMLMethodModel* umlMethodModel);
private:
    QList<UMLMethodParameterModel *> parameters;
};

#endif // UMLMETHODMODEL_H
