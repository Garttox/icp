#include "umlidentifier.h"
#include "umlaccesstype.h"

UMLIdentifier::UMLIdentifier(QString name, QString type, UMLAccessType *access)
{
    this->name = name;
    this->type = type;
    this->access = access;
}

UMLIdentifier::~UMLIdentifier()
{
    delete access;
}

QString UMLIdentifier::getName()
{
    return name;
}

QString UMLIdentifier::getType()
{
    return type;
}

UMLAccessType *UMLIdentifier::getAccess()
{
    return access;
}
