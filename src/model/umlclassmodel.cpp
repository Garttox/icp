/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umlclassmodel.cpp
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#include <QJsonObject>
#include <QJsonArray>

#include "modelprovider.h"
#include "umlclassmodel.h"
#include "umlsequencemodel.h"

#include <QDebug>

UMLClassModel::UMLClassModel(QString name, UMLClassType type, int posX, int posY) :
    name(name), type(type), posX(posX), posY(posY), fields(QList<UMLFieldModel*>()), methods(QList<UMLMethodModel*>())
{}

UMLClassModel::UMLClassModel(QString name, UMLClassType type, QList<UMLFieldModel*> fields, QList<UMLMethodModel*> methods, int posX, int posY) :
    name(name), type(type), posX(posX), posY(posY), fields(fields), methods(methods)
{}

UMLClassModel::UMLClassModel(const UMLClassModel &original) :
    QObject(),
    name(original.name), type(original.type), posX(original.posX), posY(original.posY)
{
    foreach(UMLFieldModel *field, original.fields)
    {
        UMLFieldModel *copy = new UMLFieldModel(*field);
        this->fields.append(copy);
    }
    foreach(UMLMethodModel *method, original.methods)
    {
        UMLMethodModel *copy = new UMLMethodModel(*method);
        this->methods.append(copy);
    }
}

UMLClassModel::~UMLClassModel()
{
    qDeleteAll(fields.begin(), fields.end());
    qDeleteAll(methods.begin(), methods.end());
}

void UMLClassModel::setModel(UMLClassModel &foreign)
{
    qDeleteAll(fields.begin(), fields.end());
    fields.clear();

    this->name = foreign.name;
    this->type = foreign.type;

    foreach(auto field, foreign.fields)
    {
        UMLFieldModel *copy = new UMLFieldModel(*field);
        this->fields.append(copy);
    }

    setMethodsFromCopy(foreign);

    emit modelChanged(this);
}

void UMLClassModel::setName(QString name)
{
    this->name = name;
    emit modelChanged(this);
}

void UMLClassModel::setPosition(int x, int y)
{
    this->posX = x;
    this->posY = y;
    emit modelChanged(this);
}

void UMLClassModel::addMethod(UMLMethodModel *method)
{

    methods.append(method);
    connect(method, &UMLMethodModel::modelChanged, this, &UMLClassModel::methodModelChanged);
    emit modelChanged(this);
}

void UMLClassModel::addField(UMLFieldModel *field)
{
    fields.append(field);
    connect(field, &UMLFieldModel::modelChanged, this, &UMLClassModel::fieldModelChanged);
    emit modelChanged(this);
}

void UMLClassModel::removeFieldAt(int index)
{
    UMLFieldModel *umlFieldModel = fields.takeAt(index);
    emit modelChanged(this);
    delete umlFieldModel;
}

void UMLClassModel::removeMethodAt(int index)
{
    UMLMethodModel *umlMethodModel = methods.takeAt(index);
    emit modelChanged(this);
    delete umlMethodModel;
}

bool UMLClassModel::haveIdentifierWithSignature(QString signature) const
{
    foreach (UMLAttribute *identifier, getIdentifiers())
    {
        if (identifier->toString() == signature)
        {
            return true;
        }
    }
    return false;
}

QString UMLClassModel::getName() const
{
    return name;
}

UMLClassType UMLClassModel::getType() const
{
    return type;
}

QString UMLClassModel::getDisplayName() const
{
    if (type == UMLClassType::INTERFACE)
    {
        return QString("%1 <<%2>>").arg(name, "interface");
    }
    return name;
}

QList<UMLMethodModel *> UMLClassModel::getMethods() const
{
    return methods;
}

QList<UMLFieldModel *> UMLClassModel::getFields() const
{
    return fields;
}

QSet<UMLAttribute *> UMLClassModel::getIdentifiers() const
{
    QSet<UMLAttribute *> identifiers;
    foreach (UMLFieldModel *field, fields)
    {
        identifiers.insert(field);
    }
    foreach (UMLMethodModel *method, methods)
    {
        identifiers.insert(method);
    }
    return identifiers;
}

UMLFieldModel* UMLClassModel::getFieldAt(int index) const
{
    return fields.at(index);
}

UMLMethodModel* UMLClassModel::getMethodAt(int index) const
{
    return methods.at(index);
}

UMLMethodModel *UMLClassModel::findMethodByName(QString methodName) const
{
    foreach (UMLMethodModel *method, methods)
    {
        if (method->getName() == methodName)
            return method;
    }
    return nullptr;
}

int UMLClassModel::getPosX() const
{
    return posX;
}

int UMLClassModel::getPosY() const
{
    return posY;
}

// - - - - - public slots - - - - -

void UMLClassModel::fieldModelChanged()
{
    emit modelChanged(this);
}

void UMLClassModel::methodModelChanged()
{
    emit modelChanged(this);
}

// - - - - - private  - - - - -

UMLMethodModel *UMLClassModel::takeMethodByOid(QUuid oid)
{
    QMutableListIterator<UMLMethodModel*> iter(this->methods);
    while (iter.hasNext())
    {
        UMLMethodModel *method = iter.next();
        if (method->getOid() == oid)
        {
            iter.remove();
            return method;
        }
    }
    return nullptr;
}

void UMLClassModel::setMethodsFromCopy(UMLClassModel &foreign)
{
    /*
    Methods merging is done based on oids:
    If method from foreign has oid similar with one of own methods,
    then data are set from foreign to own method, without creating copy.
    */

    QMutableListIterator<UMLMethodModel*> iter(this->methods);
    while (iter.hasNext())
    {
        UMLMethodModel *method = iter.next();
        UMLMethodModel *methodCopy = foreign.takeMethodByOid(method->getOid());
        if (methodCopy != nullptr)
        {
            method->setModelData(methodCopy);
            delete methodCopy;
        }
        else
        {
            QList<UMLSequenceModel*> umlSequenceModels = ModelProvider::getInstance().getModel()->getSequences();
            foreach (auto umlSequenceModel, umlSequenceModels)
            {
                foreach (auto umlCallModel, umlSequenceModel->getCalls())
                {
                    if (umlCallModel->getMethod() == method)
                    {
                        umlSequenceModel->removeCall(umlCallModel);
                    }
                }
            }
            iter.remove();
            delete method;
        }
    }
    foreach(auto method, foreign.methods)
    {
        UMLMethodModel *copy = new UMLMethodModel(*method);
        this->methods.append(copy);
    }
}

