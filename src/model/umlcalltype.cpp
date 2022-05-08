/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlcalltype.cpp
 * @author Michal Trlica (xtrlic02)
 */
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

QString UMLCallType::toString() const
{
    switch (type)
    {
        case MESSAGE:
            return QString("Message");
        case CREATE:
            return QString("Create");
        case DESTROY:
            return QString("Destroy");
    }
}
