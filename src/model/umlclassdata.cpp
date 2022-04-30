#include <QJsonObject>
#include <QJsonArray>

#include "umlclassdata.h"

#include <QDebug>

UMLClassData::UMLClassData(QString name, UMLClassType type, int posX, int posY) :
    name(name), type(type), posX(posX), posY(posY), fields(QList<UMLFieldData*>()), methods(QList<UMLMethodData*>())
{}

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
    qDeleteAll(fields.begin(), fields.end());
    qDeleteAll(methods.begin(), methods.end());
}

void UMLClassData::setData(const UMLClassData &data)
{
    // delete current data
    qDeleteAll(fields.begin(), fields.end());
    qDeleteAll(methods.begin(), methods.end());
    fields.clear();
    methods.clear();

    // set new data
    this->name = data.name;
    this->type = data.type;
    foreach(UMLFieldData *field, data.fields)
    {
        UMLFieldData *copy = new UMLFieldData(*field);
        this->fields.append(copy);
    }
    foreach(UMLMethodData *method, data.methods)
    {
        UMLMethodData *copy = new UMLMethodData(*method);
        this->methods.append(copy);
    }
    emit modelChanged(this);
}

void UMLClassData::setName(QString name)
{
    this->name = name;
    emit modelChanged(this);
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

void UMLClassData::addMethod(UMLMethodData *method)
{

    methods.append(method);
    connect(method, &UMLMethodData::modelChanged, this, &UMLClassData::methodModelChanged);
    emit modelChanged(this);
}

void UMLClassData::addField(UMLFieldData *field)
{
    fields.append(field);
    connect(field, &UMLFieldData::modelChanged, this, &UMLClassData::fieldModelChanged);
    emit modelChanged(this);
}

void UMLClassData::removeFieldAt(int index)
{
    UMLFieldData *umlFieldData = fields.takeAt(index);
    emit modelChanged(this);
    delete umlFieldData;
}

void UMLClassData::removeMethodAt(int index)
{
    UMLMethodData *umlMethodData = methods.takeAt(index);
    emit modelChanged(this);
    delete umlMethodData;
}

bool UMLClassData::haveIdentifierWithSignature(QString signature) const
{
    foreach (UMLIdentifier *identifier, getIdentifiers())
    {
        if (identifier->toString() == signature)
        {
            return true;
        }
    }
    return false;
}

QString UMLClassData::getName() const
{
    return name;
}

UMLClassType UMLClassData::getType() const
{
    return type;
}

QString UMLClassData::getDisplayName() const
{
    if (type == UMLClassType::INTERFACE)
        return QString("%1 <<%2>>").arg(name, "interface");
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

QSet<UMLIdentifier *> UMLClassData::getIdentifiers() const
{
    QSet<UMLIdentifier *> identifiers;
    foreach (UMLFieldData *field, fields)
    {
        identifiers.insert(field);
    }
    foreach (UMLMethodData *method, methods)
    {
        identifiers.insert(method);
    }
    return identifiers;
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
    emit modelChanged(this);
}

void UMLClassData::methodModelChanged()
{
    emit modelChanged(this);
}
