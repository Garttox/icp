#include <QJsonObject>
#include <QJsonArray>

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

bool UMLClassData::loadData(QJsonObject jsonClassData)
{
    // read fields
    foreach (auto fieldEl, jsonClassData["fields"].toArray())
    {
        if (fieldEl.toObject()["name"].isNull() || fieldEl.toObject()["type"].isNull() ||
                fieldEl.toObject()["access"].isNull())
        {
            return false;
        }
        QString name = fieldEl.toObject()["name"].toString();
        QString type = fieldEl.toObject()["type"].toString();
        UMLAccessType access = UMLAccessType(fieldEl.toObject()["access"].toString());
        UMLFieldData *field = new UMLFieldData(name, type, access);
        addField(field);
    }

    // read methods
    foreach (auto methodEl, jsonClassData["methods"].toArray())
    {
        if (methodEl.toObject()["name"].isNull() || methodEl.toObject()["type"].isNull() ||
                methodEl.toObject()["access"].isNull())
        {
            return false;
        }
        QString name = methodEl.toObject()["name"].toString();
        QString type = methodEl.toObject()["type"].toString();
        UMLAccessType access = UMLAccessType(methodEl.toObject()["access"].toString());
        UMLMethodData *method = new UMLMethodData(name, type, access);
        bool loadedSuccesfully = method->loadData(methodEl.toObject());
        if (!loadedSuccesfully)
            return false;
        addMethod(method);
    }

    return true;
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

QString UMLClassData::getDisplayName() const
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
