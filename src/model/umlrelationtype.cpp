#include "umlrelationtype.h"

UMLRelationType::UMLRelationType(UMLRelationTypeEnum type)
    : type(type)
{}

UMLRelationType::UMLRelationType(QString strType)
{
    if (strType == "ASSOCIATION")
        type = ASSOCIATION;
    else if (strType == "AGREGATION")
        type = AGREGATION;
    else if (strType == "COMPOSITION")
        type = COMPOSITION;
    else if (strType == "GENERALISATION")
        type = GENERALISATION;
    else
        type = ASSOCIATION;
}
