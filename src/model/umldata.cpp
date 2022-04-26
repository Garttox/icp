#include "umldata.h"

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

void UMLData::addClass(UMLClassData *classData)
{
    classes->insert(classData);
    connect(classData, &UMLClassData::modelChanged, this, &UMLData::classModelChanged);
    emit classModelAdded(classData);
}

void UMLData::addRelation(UMLRelationData *relation)
{
    relations->insert(relation);
}

void UMLData::clearData()
{
    emit umlModelCleared();
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

// slots
void UMLData::classModelChanged()
{
}

void UMLData::relationModelChanged()
{
}
