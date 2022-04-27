#include "umlclassdata.h"

#include <QDebug>

UMLClassData::UMLClassData(QString name, UMLClassType type, int posX, int posY) :
    name(name), type(type), posX(posX), posY(posY), fields(QList<UMLFieldData*>()), methods(QList<UMLMethodData*>())
{
}

UMLClassData::UMLClassData(const UMLClassData &original) :
    QObject(),
    name(original.name), type(original.type), posX(original.posX), posY(original.posY)
{
    foreach(UMLFieldData *field, original.fields) {
        UMLFieldData *copy = new UMLFieldData(*field);
        this->fields.append(copy);
    }
    foreach(UMLMethodData *method, original.methods) {
        UMLMethodData *copy = new UMLMethodData(*method);
        this->methods.append(copy);
    }
}

UMLClassData::~UMLClassData()
{
    foreach (UMLFieldData *field, fields)
        delete field;
    foreach (UMLMethodData *method, methods)
        delete method;
}

void UMLClassData::setData(const UMLClassData &data)
{
    this->name = data.name;
    this->type = data.type;

    this->fields.clear();
    foreach(UMLFieldData *field, data.fields)
    {
        UMLFieldData *copy = new UMLFieldData(*field);
        this->fields.append(copy);
    }

    this->methods.clear();
    foreach(UMLMethodData *method, data.methods)
    {
        UMLMethodData *copy = new UMLMethodData(*method);
        this->methods.append(copy);
    }
}

void UMLClassData::setName(QString name)
{
    this->name = name;
}

void UMLClassData::addMethod(UMLMethodData *method)
{
    methods.append(method);
    connect(method, &UMLMethodData::modelChanged, this, &UMLClassData::methodModelChanged);
}

void UMLClassData::addField(UMLFieldData *field)
{
    fields.append(field);
    connect(field, &UMLFieldData::modelChanged, this, &UMLClassData::fieldModelChanged);
}

void UMLClassData::removeFieldAt(int index)
{
    delete fields.takeAt(index);
}

void UMLClassData::removeMethodAt(int index)
{
    delete methods.takeAt(index);
}

QString UMLClassData::getName() const
{
    return name;
}

QString UMLClassData::getDisplayName() const
{
    if (type == UMLClassType::INTERFACE)
        return QString("%1 <<%2>>").arg(name, "Interface");
    return name;
}

QList<UMLMethodData *> UMLClassData::getMethods() const
{
    return methods;
}

QList<UMLFieldData *> UMLClassData::getFields() const
{
    return fields;
}

UMLFieldData* UMLClassData::getFieldAt(int index) const
{
    return fields.at(index);
}

UMLMethodData* UMLClassData::getMethodAt(int index) const
{
    return methods.at(index);
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
