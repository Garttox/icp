#include "umlmethodparametermodel.h"

UMLMethodParameterModel::UMLMethodParameterModel(QString name, QString type)
{
    this->name = name;
    this->type = type;
}

QString UMLMethodParameterModel::toString() const
{
    return QString("%1: %2").arg(name, type);
}

QString UMLMethodParameterModel::getName() const
{
    return this->name;
}

QString UMLMethodParameterModel::getType() const
{
    return this->type;
}

QJsonObject UMLMethodParameterModel::getSaveData()
{
    QJsonObject object;
    object.insert("name", name);
    object.insert("type", type);
    return object;
}

