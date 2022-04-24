#ifndef UMLACCESSTYPE_H
#define UMLACCESSTYPE_H

#include <QString>
enum UMLAccessTypeEnum {
    PUBLIC,
    PRIVATE,
    PROTECTED,
    PACKAGE
};
class UMLAccessType
{
public:
    UMLAccessType(UMLAccessTypeEnum type);
    QString toString();
    static UMLAccessTypeEnum toType(QString strType);
private:
    UMLAccessTypeEnum type;
};

#endif // UMLACCESSTYPE_H
