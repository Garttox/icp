#include "umlmethodparameterdata.h"

UMLMethodParameterData::UMLMethodParameterData(QString name, QString type)
{
    this->name = name;
    this->type = type;
}

QString UMLMethodParameterData::toString()
{
    return QString("%1: %2").arg(name, type);
}
