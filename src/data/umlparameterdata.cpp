#include "umlparameterdata.h"


bool UMLParameterData::load(QJsonObject object)
{
    auto name = object["name"];
    auto type = object["type"];

    if (hasNull(name, type))
    {
        return false;
    }

    this->name = name.toString();
    this->type = type.toString();

    return true;
}

void UMLParameterData::fromModel(UMLParameterModel *model)
{
    // TODO
}

UMLParameterModel *UMLParameterData::toModel()
{
    // TODO
}

QString UMLParameterData::getName() const
{
    return name;
}

QString UMLParameterData::getType() const
{
    return type;
}
