#ifndef UMLFIELDMODEL_H
#define UMLFIELDMODEL_H

#include <QObject>
#include <QJsonObject>
#include "umlattribute.h"

class UMLFieldModel : public UMLAttribute
{
    Q_OBJECT
public:
    UMLFieldModel(QString name, QString type, UMLAccessType access);
    UMLFieldModel(const UMLFieldModel& original);
    ~UMLFieldModel() {};
    QString toString() const override;
    QJsonObject getSaveData();
signals:
    void modelChanged();
};

#endif // UMLFIELDMODEL_H