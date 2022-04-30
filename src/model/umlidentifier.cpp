#include "umlidentifier.h"

UMLIdentifier::UMLIdentifier(QString name, QString type, UMLAccessType access)
    : QObject(), name(name), type(type), access(access)
{}

UMLIdentifier::~UMLIdentifier()
{
}

QString UMLIdentifier::getName() const
{
    return name;
}

QString UMLIdentifier::getType() const
{
    return type;
}

UMLAccessType UMLIdentifier::getAccess() const
{
    return access;
}

QString UMLIdentifier::toString() const
{
    return QString();
}

void UMLIdentifier::setName(QString name)
{
    this->name = name;
    emit modelChanged(this);
}

void UMLIdentifier::setType(QString type)
{
    this->type = type;
    emit modelChanged(this);
}

void UMLIdentifier::setAccess(UMLAccessType access)
{
    this->access = access;
    emit modelChanged(this);
}
