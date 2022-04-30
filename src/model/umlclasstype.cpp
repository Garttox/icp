#include "umlclasstype.h"

UMLClassType::UMLClassType(ClassType classType)
    : type(classType)
{}

UMLClassType::UMLClassType(QString string)
{
    type = (string == "Class") ? CLASS : INTERFACE;
}

bool UMLClassType::operator==(const ClassType rhs) const
{
    return type == rhs;
}

QString UMLClassType::toString() const
{
    return type == CLASS ? QString("Class") : QString("Interface");
}

bool UMLClassType::operator==(const UMLClassType& rhs) const
{
    return type == rhs.type;
}
