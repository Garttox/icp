/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlaccesstype.cpp
 * @author Michal Trlica (xtrlic02)
 */
#include "umlaccesstype.h"

UMLAccessType::UMLAccessType(AccessType type)
    : type(type)
{}

UMLAccessType::UMLAccessType(QString string)
{
    if (string == "Public" || string == "+")
        type = PUBLIC;
    else if (string == "Private" || string == "-")
        type = PRIVATE;
    else if (string == "Protected" || string == "#")
        type = PROTECTED;
    else if (string == "Package"  || string == "~")
        type = PACKAGE;
    else
        type = PUBLIC;
}

QString UMLAccessType::toString() const
{
    switch(type)
    {
        case PUBLIC:
            return QString("Public");
        case PRIVATE:
            return QString("Private");
        case PROTECTED:
            return QString("Protected");
        case PACKAGE:
            return QString("Package");
        default:
            return "";
    }
}

QString UMLAccessType::toAnnotationString() const
{
    switch(type)
    {
        case PUBLIC:
            return "+";
        case PRIVATE:
            return "-";
        case PROTECTED:
            return "#";
        case PACKAGE:
            return "~";
        default:
            return "";
    }
}

bool UMLAccessType::operator==(const AccessType rhs)
{
    return type == rhs;
}

QStringList UMLAccessType::asStringListFor(UMLClassType classType)
{
    QStringList classTypes = { "Public", "Private", "Protected", "Package" };
    QStringList interfaceTypes = { "Public" };
    return classType == UMLClassType::CLASS ? classTypes : interfaceTypes;
}

bool UMLAccessType::operator==(const UMLAccessType& rhs)
{
    return type == rhs.type;
}
