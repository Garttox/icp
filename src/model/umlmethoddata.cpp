#include "umlmethoddata.h"

UMLMethodData::UMLMethodData(QString name, QString type, UMLAccessType *access) :
    UMLIdentifier(name, type, access)
{
}

UMLMethodData::~UMLMethodData()
{
    foreach(UMLMethodParameterData *parameter, parameters)
        delete parameter;
}

void UMLMethodData::addParameter(UMLMethodParameterData *parameter)
{
    parameters.append(parameter);
    connect(parameter, &UMLMethodParameterData::modelChanged, this, &UMLMethodData::parameterModelChanged);
}

QString UMLMethodData::toString()
{
    QString str = QString("%1 %2(").arg(access->toString(), name);
    foreach(UMLMethodParameterData *parameter, parameters)
        str.append(parameter->toString());
    str.append("): ");
    str.append(type);
    return str;
}

// Slots

void UMLMethodData::parameterModelChanged()
{

}
