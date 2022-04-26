#include "umlmethoddata.h"

UMLMethodData::UMLMethodData(QString name, QString type, UMLAccessType access) :
    UMLIdentifier(name, type, access)
{}

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
    QStringList paramList;
    foreach(UMLMethodParameterData *parameter, parameters)
        paramList.append(parameter->toString());

    return QString("%1 %2(%3): %4").arg(access.toString(), name, paramList.join(", "), type);
}

// Slots

void UMLMethodData::parameterModelChanged()
{

}
