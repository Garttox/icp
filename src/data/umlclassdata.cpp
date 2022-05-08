/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlclassdata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlclassdata.h"

UMLClassData::UMLClassData()
{}

UMLClassData::UMLClassData(QString name) :
    name(name)
{}

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
    auto fields = fromJsonArray<UMLFieldData>(object["fields"]);
    auto methods = fromJsonArray<UMLMethodData>(object["methods"]);

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
    this->type = model->getType().toString();
    this->name = model->getName();
    this->posX = model->getPosX();
    this->posY = model->getPosY();
    this->fields = fromModels<UMLFieldModel, UMLFieldData>(model->getFields());
    this->methods = fromModels<UMLMethodModel, UMLMethodData>(model->getMethods());
}

QJsonObject UMLClassData::toJson() const
{
    QJsonObject object;
    object.insert("type", type);
    object.insert("name", name);
    object.insert("posX", posX);
    object.insert("posY", posY);
    object.insert("fields", toJsonArray(fields));
    object.insert("methods", toJsonArray(methods));
    return object;
}

UMLClassModel *UMLClassData::toModel(void */*context*/)
{
    UMLClassType umlClassType(type);
    QList<UMLFieldModel*> umlFieldModels = toModels<UMLFieldData, UMLFieldModel>(fields);
    QList<UMLMethodModel*> umlMethodModels = toModels<UMLMethodData, UMLMethodModel>(methods);
    UMLClassModel* umlClassModel = new UMLClassModel(name, umlClassType, umlFieldModels, umlMethodModels, posX, posY);
    return umlClassModel;
}

void UMLClassData::addMethod(UMLMethodData *umlMethodData)
{
    methods.append(umlMethodData);
}

void UMLClassData::setName(QString name)
{
    this->name = name;
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

bool UMLClassData::hasMethodWithName(QString name)
{
    foreach (auto method, methods)
    {
        if (method->getName() == name)
        {
            return true;
        }
    }
    return false;
}
