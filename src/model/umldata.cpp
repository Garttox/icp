#include <QJsonObject>
#include <QJsonArray>

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

void UMLData::loadData(QJsonObject json)
{
    // read classes
    foreach (auto clsEl, json["classes"].toArray())
    {
        QString name = clsEl.toObject()["name"].toString();
        UMLClassType type = UMLClassType(clsEl.toObject()["type"].toString());
        int posX = clsEl.toObject()["posX"].toInt();
        int posY = clsEl.toObject()["posY"].toInt();
        UMLClassData *classData = new UMLClassData(name, type, posX, posY);
        classData->loadData(clsEl.toObject());
        addClass(classData);
    }

    // read relations
    foreach (auto relationEl, json["relations"].toArray())
    {
        UMLClassData *source = findClassByName(relationEl.toObject()["source"].toString());
        UMLClassData *destination = findClassByName(relationEl.toObject()["destination"].toString());
        UMLRelationType *type = new UMLRelationType(relationEl.toObject()["type"].toString());
        UMLRelationData *relation = new UMLRelationData(source, destination, type);

        addRelation(relation);
    }
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
