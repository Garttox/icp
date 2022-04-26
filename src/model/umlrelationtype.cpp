#include "umlrelationtype.h"

UMLRelationType::UMLRelationType(RelationType type)
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

bool UMLRelationType::operator==(const RelationType rhs)
{
    return type == rhs;
}

bool UMLRelationType::operator==(const UMLRelationType& rhs)
{
    return type == rhs.type;
}
