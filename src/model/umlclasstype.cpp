/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlclasstype.cpp
 * @author Michal Trlica (xtrlic02)
 */
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
