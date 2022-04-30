#include "umlrelationtype.h"

UMLRelationType::UMLRelationType(RelationType type)
    : type(type)
{}

UMLRelationType::UMLRelationType(QString strType)
{
    QString normalized = strType.toUpper();
    if (normalized == "ASSOCIATION")
        type = ASSOCIATION;
    else if (normalized == "AGREGATION")
        type = AGREGATION;
    else if (normalized == "COMPOSITION")
        type = COMPOSITION;
    else if (normalized == "GENERALISATION")
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
