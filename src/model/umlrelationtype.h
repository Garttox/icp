#ifndef UMLRELATIONTYPE_H
#define UMLRELATIONTYPE_H

#include <QString>

class UMLRelationType
{
public:
    enum UMLRelationTypeEnum {
        ASSOCIATION,
        AGREGATION,
        COMPOSITION,
        GENERALISATION
    };
    UMLRelationType(UMLRelationTypeEnum type);
    UMLRelationType(QString strType);
    static UMLRelationTypeEnum toType(QString strType);
private:
    UMLRelationTypeEnum type;
};

#endif // UMLRELATIONTYPE_H
