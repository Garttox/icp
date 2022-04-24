#include "umlrelationtype.h"

UMLRelationType::UMLRelationType(UMLRelationTypeEnum type)
    : type(type)
{}

UMLRelationTypeEnum UMLRelationType::toType(QString strType)
{
    if (strType == "ASSOCIATION")
        return ASSOCIATION;
    else if (strType == "AGREGATION")
        return AGREGATION;
    else if (strType == "COMPOSITION")
        return COMPOSITION;
    else if (strType == "GENERALISATION")
        return GENERALISATION;
    else
        return ASSOCIATION;
}
