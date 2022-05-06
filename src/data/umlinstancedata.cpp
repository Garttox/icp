#include "umlinstancedata.h"

bool UMLInstanceData::load(QJsonObject object)
{
    auto name = object["name"];
    auto umlClass = object["class"];
    auto posX = object["posX"];

    if (hasNull(name, umlClass, posX))
    {
        return false;
    }

    this->name = name.toString();
    this->umlClass = umlClass.toString();
    this->posX = posX.toInt();

    return true;
}

void UMLInstanceData::fromModel(UMLInstanceModel *model)
{
    // TODO
}

UMLInstanceModel *UMLInstanceData::toModel()
{
    // TODO
}

QString UMLInstanceData::getName() const
{
    return name;
}

QString UMLInstanceData::getUmlClass() const
{
    return umlClass;
}

int UMLInstanceData::getPosX() const
{
    return posX;
}
