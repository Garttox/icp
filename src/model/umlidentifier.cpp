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
