#include "umlinstancedata.h"

UMLInstanceData::UMLInstanceData(QString name, UMLClassData *umlClassData, int posX) :
    name(name), umlClassData(umlClassData), posX(posX)
{}

QString UMLInstanceData::getDisplayName() const
{
    return QString("%1:%2").arg(this->name, this->umlClassData->getName());
}

QString UMLInstanceData::getName() const
{
    return this->name;
}

void UMLInstanceData::setName(QString name)
{
    this->name = name;
}

int UMLInstanceData::getPosX() const
{
    return this->posX;
}

void UMLInstanceData::setPosX(int posX)
{
    this->posX = posX;
}

UMLClassData *UMLInstanceData::getClassData()
{
    return this->umlClassData;
}
