#include "umlmethoddata.h"
#include "umlmethodparameterdata.h"
#include "umlaccesstype.h"

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
}
