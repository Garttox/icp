#include <QJsonObject>
#include <QJsonArray>

#include "umlmethoddata.h"

UMLMethodData::UMLMethodData(QString name, QString type, UMLAccessType access) :
    UMLIdentifier(name, type, access)
{}

UMLMethodData::UMLMethodData(const UMLMethodData &original) :
    UMLIdentifier(original.name, original.type, original.access)
{
    foreach(UMLMethodParameterData *parameter, original.parameters)
    {
        QString name = parameter->getName();
        QString type = parameter->getType();
        this->parameters.append(new UMLMethodParameterData(name, type));
    }
}

UMLMethodData::~UMLMethodData()
{
    qDeleteAll(parameters);
}

bool UMLMethodData::loadData(QJsonObject jsonMethodData)
{
    foreach (auto parameterEl, jsonMethodData["parameters"].toArray())
    {
        if (parameterEl.toObject()["name"].isNull() || parameterEl.toObject()["type"].isNull())
            return false;
        QString name = parameterEl.toObject()["name"].toString();
        QString type = parameterEl.toObject()["type"].toString();
        UMLMethodParameterData *parameter = new UMLMethodParameterData(name, type);
        addParameter(parameter);
    }
    return true;
}

void UMLMethodData::addParameter(UMLMethodParameterData *parameter)
{
    parameters.append(parameter);
    connect(parameter, &UMLMethodParameterData::modelChanged, this, &UMLMethodData::parameterModelChanged);
    emit modelChanged(this);
}

QString UMLMethodData::toString() const
{
    QStringList paramList;
    foreach(UMLMethodParameterData *parameter, parameters)
    {
        paramList.append(parameter->toString());
    }

    return QString("%1 %2(%3): %4").arg(access.toAnnotationString(), name, paramList.join(", "), type);
}

QList<UMLMethodParameterData *> UMLMethodData::getParameters() const
{
    return this->parameters;
}

void UMLMethodData::clearParameters()
{
    parameters.clear();
    emit modelChanged(this);
}

// Slots

void UMLMethodData::parameterModelChanged()
{
    emit modelChanged(this);
}
