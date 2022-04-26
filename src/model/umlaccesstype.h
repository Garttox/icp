#ifndef UMLACCESSTYPE_H
#define UMLACCESSTYPE_H

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
    QString toDisplayString() const;
    bool operator==(const AccessType rhs);
    bool operator==(const UMLAccessType& rhs);

    static QStringList asStringList();

private:
    AccessType type;
};

#endif // UMLACCESSTYPE_H
