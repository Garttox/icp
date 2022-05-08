/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlaccesstype.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef UMLACCESSTYPE_H
#define UMLACCESSTYPE_H

#include "model/umlclasstype.h"
#include <QString>
#include <QStringList>

class UMLAccessType
{
public:
    enum AccessType
    {
        PUBLIC,
        PRIVATE,
        PROTECTED,
        PACKAGE
    };
    UMLAccessType(AccessType type);
    UMLAccessType(QString type);

    QString toString() const;
    QString toAnnotationString() const;
    bool operator==(const AccessType rhs);
    bool operator==(const UMLAccessType& rhs);

    static QStringList asStringListFor(UMLClassType classType);

private:
    AccessType type;
};

#endif // UMLACCESSTYPE_H
