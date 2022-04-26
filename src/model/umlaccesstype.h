#ifndef UMLACCESSTYPE_H
#define UMLACCESSTYPE_H

#include <QString>

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
    QString toString();
private:
    AccessType type;
};

#endif // UMLACCESSTYPE_H
