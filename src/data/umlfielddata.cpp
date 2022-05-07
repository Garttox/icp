/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlfielddata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlfielddata.h"

bool UMLFieldData::load(QJsonObject object)
{
    auto name = object["name"];
    auto type =  object["type"];
    auto access =  object["type"];

    if (hasNull(name, type, access))
    {
        return false;
    }

    this->name = name.toString();
    this->type = type.toString();
    this->access = type.toString();

    return true;
}

void UMLFieldData::fromModel(UMLFieldModel *model)
{
    this->name = model->getName();
    this->type = model->getType();
    this->access = model->getAccess().toString();
}

QJsonObject UMLFieldData::toJson() const
{
    QJsonObject object;
    object.insert("name", name);
    object.insert("type", type);
    object.insert("access", access);
    return object;
}

UMLFieldModel *UMLFieldData::toModel(void */*context*/)
{
    UMLAccessType umlAccessType(access);
    UMLFieldModel *umlFieldModel = new UMLFieldModel(name, type, umlAccessType);
    return umlFieldModel;
}
