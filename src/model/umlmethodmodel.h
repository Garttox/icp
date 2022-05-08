/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlmethodmodel.h
 * @author Michal Trlica (xtrlic02)
 */
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
    UMLMethodModel(QString name, QString type, UMLAccessType access, QList<UMLParameterModel *> parameters);
    UMLMethodModel(const UMLMethodModel &original);
    ~UMLMethodModel();
    void addParameter(UMLParameterModel *parameter);
    QString toString() const override;
    QList<UMLParameterModel *> getParameters() const;
    void clearParameters();
    void setModelData(UMLMethodModel *copy);
    QUuid getOid() const;

public slots:
    void parameterModelChanged();

signals:
    void modelChanged(UMLMethodModel* umlMethodModel);

private:
    QUuid oid;
    QList<UMLParameterModel *> parameters;
};

#endif // UMLMETHODMODEL_H
