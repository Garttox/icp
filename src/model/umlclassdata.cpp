#include "umlclassdata.h"
#include "umlfielddata.h"
#include "umlmethoddata.h"

UMLClassData::UMLClassData(QString name, UMLClassType type, int posX, int posY) :
    name(name), type(type), posX(posX), posY(posY), fields(new QSet<UMLFieldData*>()), methods(new QSet<UMLMethodData*>())
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

void UMLClassData::addMethod(UMLMethodData *method)
{
    methods->insert(method);
}

void UMLClassData::addField(UMLFieldData *field)
{
    fields->insert(field);
}

QString UMLClassData::getName()
{
    if (type == INTERFACE)
        return QString("%1 <<%2>>").arg(name, "Interface");
    return name;
}

QSet<UMLMethodData *> *UMLClassData::getMethods()
{
    return methods;
}

QSet<UMLFieldData *> *UMLClassData::getFields()
{
    return fields;
}

int UMLClassData::getPosX()
{
    return posX;
}

int UMLClassData::getPosY()
{
    return posY;
}