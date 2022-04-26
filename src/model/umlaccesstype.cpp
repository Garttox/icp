#include "umlaccesstype.h"

UMLAccessType::UMLAccessType(AccessType type)
    : type(type)
{}

UMLAccessType::UMLAccessType(QString strType)
{
    if (strType == "PUBLIC")
        type = PUBLIC;
    else if (strType == "PRIVATE")
        type = PRIVATE;
    else if (strType == "PROTECTED")
        type = PROTECTED;
    else if (strType == "PACKAGE")
        type = PACKAGE;
    else
        type = PUBLIC;
}

QString UMLAccessType::toString()
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

bool UMLAccessType::operator==(const UMLAccessType& rhs)
{
    return type == rhs.type;
}
