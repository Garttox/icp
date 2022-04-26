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
            break;
        case PRIVATE:
            return "-";
            break;
        case PROTECTED:
            return "#";
            break;
        case PACKAGE:
            return "~";
            break;
        default:
            return "";
            break;
    }
}
