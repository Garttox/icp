#ifndef UMLFIELDDATA_H
#define UMLFIELDDATA_H

#include "umlidentifier.h"

class UMLFieldData : public UMLIdentifier
{
public:
    UMLFieldData(QString name, QString type, UMLAccessType *access);
    QString toString();
};

#endif // UMLFIELDDATA_H
