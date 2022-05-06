#include "umlclassdata.h"

UMLClassData::~UMLClassData()
{
    qDeleteAll(fields);
    qDeleteAll(methods);
}

bool UMLClassData::load(QJsonObject object)
{
    auto type = object["type"];
    auto name =  object["name"];
    auto posX = object["posX"];
    auto posY = object["posY"];
    auto fields = loadArray<UMLFieldData>(object["fields"]);
    auto methods = loadArray<UMLMethodData>(object["methods"]);

    if (hasNull(type, name, posX, posY) || !fields.ok || !methods.ok)
    {
        return false;
    }

    this->type = type.toString();
    this->name = name.toString();
    this->posX = posX.toInt();
    this->posY = posY.toInt();
    this->fields = fields.value;
    this->methods = methods.value;

    return true;
}

void UMLClassData::fromModel(UMLClassModel *model)
{
    // TODO
}

UMLClassModel *UMLClassData::toModel()
{
    // TODO
}

QString UMLClassData::getName() const
{
    return name;
}

QString UMLClassData::getType() const
{
    return type;
}

int UMLClassData::getPosX() const
{
    return posX;
}

int UMLClassData::getPosY() const
{
    return posY;
}

QList<UMLFieldData *> UMLClassData::getFields() const
{
    return fields;
}

QList<UMLMethodData *> UMLClassData::getMethods() const
{
    return methods;
}
