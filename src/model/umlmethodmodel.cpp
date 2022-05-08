/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlmethodmodel.cpp
 * @author Michal Trlica (xtrlic02)
 */
#include <QJsonObject>
#include <QJsonArray>

#include "umlmethodmodel.h"

UMLMethodModel::UMLMethodModel(QString name, QString type, UMLAccessType access) :
    UMLAttribute(name, type, access), oid(QUuid::createUuid()), parameters(QList<UMLParameterModel*>())
{}

UMLMethodModel::UMLMethodModel(QString name, QString type, UMLAccessType access, QList<UMLParameterModel *> parameters) :
    UMLAttribute(name, type, access), oid(QUuid::createUuid()), parameters(parameters)
{}

UMLMethodModel::UMLMethodModel(const UMLMethodModel &original) :
    UMLAttribute(original.name, original.type, original.access)
{
    this->oid = original.getOid();
    foreach(UMLParameterModel *parameter, original.parameters)
    {
        QString name = parameter->getName();
        QString type = parameter->getType();
        this->parameters.append(new UMLParameterModel(name, type));
    }
}

UMLMethodModel::~UMLMethodModel()
{
    qDeleteAll(parameters);
}

void UMLMethodModel::addParameter(UMLParameterModel *parameter)
{
    parameters.append(parameter);
    connect(parameter, &UMLParameterModel::modelChanged, this, &UMLMethodModel::parameterModelChanged);
    emit modelChanged(this);
}

QString UMLMethodModel::toString() const
{
    QStringList paramList;
    foreach(UMLParameterModel *parameter, parameters)
    {
        paramList.append(parameter->toString());
    }

    return QString("%1 %2(%3): %4").arg(access.toAnnotationString(), name, paramList.join(", "), type);
}

QList<UMLParameterModel *> UMLMethodModel::getParameters() const
{
    return this->parameters;
}

void UMLMethodModel::clearParameters()
{
    parameters.clear();
    emit modelChanged(this);
}

void UMLMethodModel::setModelData(UMLMethodModel *copy)
{
    this->name = copy->name;
    this->type = copy->type;
    this->access = copy->access;

    qDeleteAll(parameters);
    parameters.clear();
    foreach(auto parameter, copy->parameters)
    {
        QString name = parameter->getName();
        QString type = parameter->getType();
        this->parameters.append(new UMLParameterModel(name, type));
    }
}

QUuid UMLMethodModel::getOid() const
{
    return oid;
}


// - - - - - public slots - - - - -

void UMLMethodModel::parameterModelChanged()
{
    emit modelChanged(this);
}
