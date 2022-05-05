#ifndef UMLFIELDDATA_H
#define UMLFIELDDATA_H

#include <QObject>
#include <QJsonObject>
#include "umlattribute.h"

class UMLFieldData : public UMLAttribute
{
    Q_OBJECT
public:
    UMLFieldData(QString name, QString type, UMLAccessType access);
    UMLFieldData(const UMLFieldData& original);
    ~UMLFieldData() {};
    QString toString() const override;
    QJsonObject getSaveData();
signals:
    void modelChanged();
};

#endif // UMLFIELDDATA_H
