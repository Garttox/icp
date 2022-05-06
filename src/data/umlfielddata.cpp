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
    // TODO
}

UMLFieldModel *UMLFieldData::toModel()
{
    // TODO
}
