#ifndef UMLIDENTIFIER_H
#define UMLIDENTIFIER_H

#include <QString>

#include "umlaccesstype.h"

class UMLIdentifier
{
public:
    UMLIdentifier(QString name, QString type, UMLAccessType access);
protected:
    QString name;
    QString type;
    UMLAccessType access;
};

#endif // UMLIDENTIFIER_H
