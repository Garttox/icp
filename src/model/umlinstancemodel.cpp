#include "umlinstancemodel.h"

UMLInstanceModel::UMLInstanceModel(QString name, UMLClassModel *umlClassModel, int posX, int posY) :
    name(name), umlClassModel(umlClassModel), posX(posX), posY(posY)
{}

QString UMLInstanceModel::getDisplayName() const
{
    return QString("%1:%2").arg(this->name, this->umlClassModel->getName());
}

QString UMLInstanceModel::getName() const
{
    return this->name;
}

void UMLInstanceModel::setName(QString name)
{
    this->name = name;
    emit modelChanged(this);
}

int UMLInstanceModel::getPosX() const
{
    return this->posX;
}

void UMLInstanceModel::setPosX(int posX)
{
    this->posX = posX;
    emit modelChanged(this);
}

int UMLInstanceModel::getPosY() const
{
    return posY;
}

void UMLInstanceModel::setPosY(int posY)
{
    this->posY = posY;
    emit modelChanged(this);
}

UMLClassModel *UMLInstanceModel::getClassModel()
{
    return this->umlClassModel;
}
