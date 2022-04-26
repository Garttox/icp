#include "umlclasstype.h"

UMLClassType::UMLClassType(ClassType classType)
    : type(classType)
{}

UMLClassType::UMLClassType(QString strClassType)
{
    if (strClassType == "CLASS")
        type = CLASS;
    else if (strClassType == "INTERFACE")
        type = INTERFACE;
    else
        type = CLASS;
}

bool UMLClassType::operator==(const ClassType rhs)
{
    return type == rhs;
}

bool UMLClassType::operator==(const UMLClassType& rhs)
{
    return type == rhs.type;
}
