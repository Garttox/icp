#ifndef UMLRELATIONTYPE_H
#define UMLRELATIONTYPE_H

#include <QString>

enum UMLRelationTypeEnum {
    ASSOCIATION,
    AGREGATION,
    COMPOSITION,
    GENERALISATION
};

class UMLRelationType
{
public:
    UMLRelationType(UMLRelationTypeEnum type);
    static UMLRelationTypeEnum toType(QString strType);
private:
    UMLRelationTypeEnum type;
};

#endif // UMLRELATIONTYPE_H
