#include "umldata.h"
#include "umlclassdata.h"
#include "umlrelationdata.h"

UMLData::UMLData() :
    classes(new QSet<UMLClassData *>()), relations(new QSet<UMLRelationData *>)
{}

UMLData::~UMLData()
{
    foreach (UMLClassData *cls, *classes)
        delete cls;

    foreach (UMLRelationData *relation, *relations)
        delete relation;
    delete relations;
    delete classes;
}

void UMLData::addClass(UMLClassData *cls)
{
    classes->insert(cls);
}

void UMLData::addRelation(UMLRelationData *relation)
{
    relations->insert(relation);
}

void UMLData::clearData()
{
    classes->clear();
    relations->clear();
}

UMLClassData* UMLData::findClassByName(QString clsName)
{
    foreach (UMLClassData *cls, *classes)
    {
        if (cls->getName() == clsName)
            return cls;
    }
    return nullptr;
}

QSet<UMLClassData *>* UMLData::getClasses()
{
    return classes;
}
