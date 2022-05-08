/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlparametermodel.cpp
 * @author Michal Trlica (xtrlic02)
 */
#include "umlparametermodel.h"

UMLParameterModel::UMLParameterModel(QString name, QString type)
{
    this->name = name;
    this->type = type;
}

QString UMLParameterModel::toString() const
{
    return QString("%1: %2").arg(name, type);
}

QString UMLParameterModel::getName() const
{
    return this->name;
}

QString UMLParameterModel::getType() const
{
    return this->type;
}
