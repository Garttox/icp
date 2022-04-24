#include "umlaccesstype.h"

UMLAccessType::UMLAccessType(UMLAccessTypeEnum type)
{
    this->type = type;
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

UMLAccessTypeEnum UMLAccessType::toType(QString strType)
{
    if (strType == "PUBLIC")
        return PUBLIC;
    else if (strType == "PRIVATE")
        return PRIVATE;
    else if (strType == "PROTECTED")
        return PROTECTED;
    else if (strType == "PACKAGE")
        return PACKAGE;
    else
        return PUBLIC;
}
