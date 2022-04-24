#include "umlclassdata.h"
#include "umlfielddata.h"
#include "umlmethoddata.h"

UMLClassData::UMLClassData(QString name, UMLClassType type, int posX, int posY)
{
    this->name = name;
    this->type = type;
    this->posX = posX;
    this->posY = posY;
}

UMLClassData::~UMLClassData()
{
    foreach (UMLFieldData *field, fields)
        delete field;
    foreach (UMLMethodData *method, methods)
        delete method;
}

void UMLClassData::addMethod(UMLMethodData *method)
{
    methods.insert(method);
}

void UMLClassData::addField(UMLFieldData *field)
{
    fields.insert(field);
}

QString UMLClassData::getName()
{
    return name;
}
