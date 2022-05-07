/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlmethoddata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlmethoddata.h"
#include "model/umlparametermodel.h"

UMLMethodData::~UMLMethodData()
{
    qDeleteAll(parameters);
}

bool UMLMethodData::load(QJsonObject object)
{
    auto name = object["name"];
    auto type =  object["type"];
    auto access =  object["type"];
    auto parameters = fromJsonArray<UMLParameterData>(object["parameters"]);

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
    this->name = model->getName();
    this->type = model->getType();
    this->access = model->getAccess().toString();
    this->parameters = fromModels<UMLParameterModel, UMLParameterData>(model->getParameters());
}

QJsonObject UMLMethodData::toJson() const
{
    QJsonObject object;
    object.insert("name", name);
    object.insert("type", type);
    object.insert("access", access);
    object.insert("parameters", toJsonArray(parameters));
    return object;
}

UMLMethodModel *UMLMethodData::toModel(void */*context*/)
{
    UMLAccessType umlAccessType(access);
    QList<UMLParameterModel *> umlParametersModels = toModels<UMLParameterData, UMLParameterModel>(this->parameters);
    UMLMethodModel *umlMethodModel = new UMLMethodModel(name, type, umlAccessType, umlParametersModels);
    return umlMethodModel;
}

QList<UMLParameterData *> UMLMethodData::getParameters() const
{
    return parameters;
}
