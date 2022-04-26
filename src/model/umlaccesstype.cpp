#include "umlaccesstype.h"

UMLAccessType::UMLAccessType(AccessType type)
    : type(type)
{}

UMLAccessType::UMLAccessType(QString strType)
{
    const QString strTypeNormalized = strType.toUpper();
    if (strTypeNormalized == "PUBLIC")
        type = PUBLIC;
    else if (strTypeNormalized == "PRIVATE")
        type = PRIVATE;
    else if (strTypeNormalized == "PROTECTED")
        type = PROTECTED;
    else if (strTypeNormalized == "PACKAGE")
        type = PACKAGE;
    else
        type = PUBLIC;
}

QString UMLAccessType::toString() const
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

QString UMLAccessType::toDisplayString() const
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

QStringList UMLAccessType::asStringList()
{
    QStringList list = { "Public", "Private", "Protected", "Package" };
    return list;
}

bool UMLAccessType::operator==(const AccessType rhs)
{
    return type == rhs;
}

bool UMLAccessType::operator==(const UMLAccessType& rhs)
{
    return type == rhs.type;
}
