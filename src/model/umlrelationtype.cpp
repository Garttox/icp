#include "umlrelationtype.h"

UMLRelationType::UMLRelationType(RelationType type)
    : type(type)
{}

UMLRelationType::UMLRelationType(QString string)
{
    if (string == "Association")
        type = ASSOCIATION;
    else if (string == "Agregation")
        type = AGREGATION;
    else if (string == "Composition")
        type = COMPOSITION;
    else if (string == "Generalisation")
        type = GENERALISATION;
    else
        type = ASSOCIATION;
}

bool UMLRelationType::operator==(const RelationType rhs)
{
    return type == rhs;
}

QString UMLRelationType::toString() const
{
    switch (type)
    {
        case ASSOCIATION:
            return QString("Association");
        case AGREGATION:
            return QString("Agregation");
        case COMPOSITION:
            return QString("Composition");
        case GENERALISATION:
            return QString("Generalisation");
    }
    return QString();
}

QStringList UMLRelationType::asStringList()
{
    QStringList list = { "Association", "Agregation", "Composition", "Generalisation" };
    return list;
}

bool UMLRelationType::operator==(const UMLRelationType& rhs)
{
    return type == rhs.type;
}
