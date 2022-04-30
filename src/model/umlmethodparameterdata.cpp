#include "umlmethodparameterdata.h"

UMLMethodParameterData::UMLMethodParameterData(QString name, QString type)
{
    this->name = name;
    this->type = type;
}

QString UMLMethodParameterData::toString() const
{
    return QString("%1: %2").arg(name, type);
}

QString UMLMethodParameterData::getName() const
{
    return this->name;
}

QString UMLMethodParameterData::getType() const
{
    return this->type;
}

QJsonObject UMLMethodParameterData::getSaveData()
{
    QJsonObject object;
    object.insert("name", name);
    object.insert("type", type);
    return object;
}

