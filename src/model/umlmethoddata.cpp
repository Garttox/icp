#include "umlmethoddata.h"

UMLMethodData::UMLMethodData(QString name, QString type, UMLAccessType access) :
    UMLIdentifier(name, type, access)
{}

UMLMethodData::UMLMethodData(const UMLMethodData &original) :
    QObject(),
    UMLIdentifier(original.name, original.type, original.access)
{
    foreach(UMLMethodParameterData *parameter, original.parameters) {
        QString name = parameter->getName();
        QString type = parameter->getType();
        this->parameters.append(new UMLMethodParameterData(name, type));
    }
}

UMLMethodData::~UMLMethodData()
{
    foreach(UMLMethodParameterData *parameter, parameters)
    {
        delete parameter;
    }
}

void UMLMethodData::addParameter(UMLMethodParameterData *parameter)
{
    parameters.append(parameter);
    connect(parameter, &UMLMethodParameterData::modelChanged, this, &UMLMethodData::parameterModelChanged);
}

QString UMLMethodData::toString()
{
    QString str = QString("%1 %2(").arg(access.toString(), name);
    foreach(UMLMethodParameterData *parameter, parameters)
        str.append(parameter->toString());
    str.append("): ");
    str.append(type);
    return str;
}

QList<UMLMethodParameterData *> UMLMethodData::getParameters() const
{
    return this->parameters;
}

void UMLMethodData::clearParameters()
{
    parameters.clear();
}

// Slots

void UMLMethodData::parameterModelChanged()
{

}
