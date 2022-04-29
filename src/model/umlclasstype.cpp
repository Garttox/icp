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

bool UMLClassType::operator==(const ClassType rhs) const
{
    return type == rhs;
}

QString UMLClassType::toDisplayString() const
{
    return type == CLASS ? QString("Class") : QString("Interface");
}

bool UMLClassType::operator==(const UMLClassType& rhs) const
{
    return type == rhs.type;
}
