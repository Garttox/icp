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
