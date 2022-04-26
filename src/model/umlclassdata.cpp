#include "umlclassdata.h"

UMLClassData::UMLClassData(QString name, UMLClassType type, int posX, int posY) :
    name(name), type(type), posX(posX), posY(posY), fields(new QList<UMLFieldData*>()), methods(new QList<UMLMethodData*>())
{
}

UMLClassData::~UMLClassData()
{
    foreach (UMLFieldData *field, *fields)
        delete field;
    foreach (UMLMethodData *method, *methods)
        delete method;
    delete methods;
    delete fields;
}

void UMLClassData::setName(QString name)
{
    this->name = name;
}

void UMLClassData::addMethod(UMLMethodData *method)
{
    methods->append(method);
    connect(method, &UMLMethodData::modelChanged, this, &UMLClassData::methodModelChanged);
}

void UMLClassData::addField(UMLFieldData *field)
{
    fields->append(field);
    connect(field, &UMLFieldData::modelChanged, this, &UMLClassData::fieldModelChanged);
}

void UMLClassData::removeFieldAt(int index)
{
    fields->removeAt(index);
}

void UMLClassData::removeMethodAt(int index)
{
    methods->removeAt(index);
}

QString UMLClassData::getName() const
{
    return name;
}

QString UMLClassData::getDisplayName()
{
    if (type == UMLClassType::INTERFACE)
        return QString("%1 <<%2>>").arg(name, "Interface");
    return name;
}

QList<UMLMethodData *> *UMLClassData::getMethods() const
{
    return methods;
}

QList<UMLFieldData *> *UMLClassData::getFields() const
{
    return fields;
}

UMLFieldData *UMLClassData::getFieldAt(int index) const
{
    return fields->at(index);
}

UMLMethodData *UMLClassData::getMethodAt(int index) const
{
    return methods->at(index);
}

int UMLClassData::getPosX() const
{
    return posX;
}

int UMLClassData::getPosY() const
{
    return posY;
}

// Slots

void UMLClassData::fieldModelChanged()
{

}

void UMLClassData::methodModelChanged()
{

}
