#ifndef UMLFIELDDATA_H
#define UMLFIELDDATA_H

#include <QObject>

#include "umlidentifier.h"

class UMLFieldData : public QObject, public UMLIdentifier
{
    Q_OBJECT
public:
    UMLFieldData(QString name, QString type, UMLAccessType *access);
    ~UMLFieldData() {};
    QString toString();
signals:
    void modelChanged();
};

#endif // UMLFIELDDATA_H
