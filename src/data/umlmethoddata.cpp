/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlmethoddata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlmethoddata.h"

UMLMethodData::~UMLMethodData()
{
    qDeleteAll(parameters);
}

bool UMLMethodData::load(QJsonObject object)
{
    auto name = object["name"];
    auto type =  object["type"];
    auto access =  object["type"];
    auto parameters = loadArray<UMLParameterData>(object["parameters"]);

    if (hasNull(name, type, access) || !parameters.ok)
    {
        return false;
    }

    this->name = name.toString();
    this->type = type.toString();
    this->access = type.toString();
    this->parameters = parameters.value;

    return true;
}

void UMLMethodData::fromModel(UMLMethodModel *model)
{
    // TODO
}

UMLMethodModel *UMLMethodData::toModel()
{
    // TODO
}

QList<UMLParameterData *> UMLMethodData::getParameters() const
{
    return parameters;
}
