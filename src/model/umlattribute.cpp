#include "umlattribute.h"

UMLAttribute::UMLAttribute(QString name, QString type, UMLAccessType access)
    : QObject(), name(name), type(type), access(access)
{}

UMLAttribute::~UMLAttribute()
{
}

QString UMLAttribute::getName() const
{
    return name;
}

QString UMLAttribute::getType() const
{
    return type;
}

UMLAccessType UMLAttribute::getAccess() const
{
    return access;
}

QString UMLAttribute::toString() const
{
    return QString();
}

void UMLAttribute::setName(QString name)
{
    this->name = name;
    emit modelChanged(this);
}

void UMLAttribute::setType(QString type)
{
    this->type = type;
    emit modelChanged(this);
}

void UMLAttribute::setAccess(UMLAccessType access)
{
    this->access = access;
    emit modelChanged(this);
}
