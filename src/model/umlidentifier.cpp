#include "umlidentifier.h"

UMLIdentifier::UMLIdentifier(QString name, QString type, UMLAccessType access)
    : name(name), type(type), access(access)
{}

UMLIdentifier::~UMLIdentifier()
{
    delete access;
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

void UMLIdentifier::setName(QString name)
{
    this->name = name;
}

void UMLIdentifier::setType(QString type)
{
    this->type = type;
}

void UMLIdentifier::setAccess(UMLAccessType access)
{
    this->access = access;
}
