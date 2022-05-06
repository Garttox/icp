#include <QJsonObject>
#include <QJsonArray>

#include "umlmethodmodel.h"

UMLMethodModel::UMLMethodModel(QString name, QString type, UMLAccessType access) :
    UMLAttribute(name, type, access)
{}

UMLMethodModel::UMLMethodModel(const UMLMethodModel &original) :
    UMLAttribute(original.name, original.type, original.access)
{
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

bool UMLMethodModel::loadData(QJsonObject jsonMethodData)
{
    foreach (auto parameterEl, jsonMethodData["parameters"].toArray())
    {
        if (parameterEl.toObject()["name"].isNull() || parameterEl.toObject()["type"].isNull())
            return false;
        QString name = parameterEl.toObject()["name"].toString();
        QString type = parameterEl.toObject()["type"].toString();
        UMLParameterModel *parameter = new UMLParameterModel(name, type);
        addParameter(parameter);
    }
    return true;
}

QJsonObject UMLMethodModel::getSaveData()
{
    QJsonObject object;
    QJsonArray parametersData;

    foreach (auto parameter, parameters)
    {
        parametersData.append(parameter->getSaveData());
    }

    object.insert("name", name);
    object.insert("type", type);
    object.insert("access", access.toString());
    object.insert("parameters", parametersData);

    return object;
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

// Slots

void UMLMethodModel::parameterModelChanged()
{
    emit modelChanged(this);
}
