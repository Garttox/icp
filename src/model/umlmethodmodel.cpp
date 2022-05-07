#include <QJsonObject>
#include <QJsonArray>

#include "umlmethodmodel.h"

UMLMethodModel::UMLMethodModel(QString name, QString type, UMLAccessType access) :
    UMLAttribute(name, type, access), parameters(QList<UMLParameterModel*>())
{}

UMLMethodModel::UMLMethodModel(QString name, QString type, UMLAccessType access, QList<UMLParameterModel *> parameters) :
    UMLAttribute(name, type, access), parameters(parameters)
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
