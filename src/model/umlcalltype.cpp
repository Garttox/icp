#include "umlcalltype.h"

UMLCallType::UMLCallType(CallType type)
    : type(type)
{}

UMLCallType::UMLCallType(QString string)
{
    if (string == "Message")
        type = MESSAGE;
    else if (string == "Create")
        type = CREATE;
    else if (string == "Destroy")
        type = DESTROY;
    else
        type = MESSAGE;
}

bool UMLCallType::operator==(const CallType rhs)
{
    return type == rhs;
}

bool UMLCallType::operator==(const UMLCallType& rhs)
{
    return type == rhs.type;
}
