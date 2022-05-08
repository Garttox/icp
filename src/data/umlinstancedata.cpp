/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlinstancedata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlinstancedata.h"
#include "model/modelprovider.h"

UMLInstanceData::UMLInstanceData()
{}

UMLInstanceData::UMLInstanceData(QString name, QString umlClass) :
    name(name), umlClass(umlClass)
{}

bool UMLInstanceData::load(QJsonObject object)
{
    auto name = object["name"];
    auto umlClass = object["class"];
    auto posX = object["posX"];
    auto posY = object["posY"];

    if (hasNull(name, umlClass, posX, posY))
    {
        return false;
    }

    this->name = name.toString();
    this->umlClass = umlClass.toString();
    this->posX = posX.toInt();
    this->posY = posY.toInt();

    return true;
}

void UMLInstanceData::fromModel(UMLInstanceModel *model)
{
    this->name = model->getName();
    this->umlClass = model->getClassModel()->getName();
    this->posX = model->getPosX();
    this->posY = model->getPosY();
}

QJsonObject UMLInstanceData::toJson() const
{
    QJsonObject object;
    object.insert("name", name);
    object.insert("class", umlClass);
    object.insert("posX", posX);
    object.insert("posY", posY);
    return object;
}

UMLInstanceModel *UMLInstanceData::toModel(void */*context*/)
{
    UMLModel* model = ModelProvider::getInstance().getModel();
    UMLClassModel* umlClassModel = model->findClassByName(umlClass);
    UMLInstanceModel *umlInstanceModel = new UMLInstanceModel(name, umlClassModel, posX, posY);
    return umlInstanceModel;
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

int UMLInstanceData::getPosY() const
{
    return posY;
}
