/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umldata.cpp
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#include <QJsonObject>
#include <QJsonArray>

#include "umldata.h"

UMLData::UMLData() :
    classes(new QSet<UMLClassData *>()), relations(new QSet<UMLRelationData *>), sequences(new QSet<UMLSequenceData *>)
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

bool UMLData::loadData(QJsonObject json)
{
    // read classes
    foreach (auto clsEl, json["classes"].toArray())
    {
        QJsonObject object = clsEl.toObject();
        if (object["name"].isNull() || object["type"].isNull() ||
                object["posX"].isNull() || object["posY"].isNull())
        {
            return false;
        }

        QString name = object["name"].toString();
        UMLClassType type = UMLClassType(object["type"].toString());
        int posX = object["posX"].toInt();
        int posY = object["posY"].toInt();
        UMLClassData *classData = new UMLClassData(name, type, posX, posY);
        bool loadedSuccesfully = classData->loadData(object);
        if (!loadedSuccesfully)
        {
            delete classData;
            return false;
        }
        addClass(classData);
    }

    // read relations
    foreach (auto relationEl, json["relations"].toArray())
    {
        QJsonObject object = relationEl.toObject();
        if (object["source"].isNull() || object["destination"].isNull() || object["type"].isNull()
                || object["sourceAnchorId"].isNull() || object["destinationAnchorId"].isNull())
        {
            return false;
        }

        UMLClassData *source = findClassByName(object["source"].toString());
        UMLClassData *destination = findClassByName(object["destination"].toString());
        UMLRelationType type(object["type"].toString());
        int sourceAnchorId = object["sourceAnchorId"].toInt();
        int destinationAnchorId = object["destinationAnchorId"].toInt();
        UMLRelationData *relation = new UMLRelationData(source, destination, type, sourceAnchorId, destinationAnchorId);
        addRelation(relation);
    }

    //read sequences
    foreach (auto sequenceEl, json["sequences"].toArray())
    {
        QJsonObject object = sequenceEl.toObject();
        if (object["name"].isNull())
        {
            return false;
        }
        QString name = object["name"].toString();
        UMLSequenceData *sequenceData = new UMLSequenceData(name);
        addSequence(sequenceData);
        bool loadedSuccesfully = sequenceData->loadData(object);
        if (!loadedSuccesfully)
        {
            removeSequence(sequenceData);
            return false;
        }
    }
    return true;
}

QJsonObject UMLData::getSaveData()
{
    QJsonObject object;
    QJsonArray classesData;
    QJsonArray relationsData;

    foreach (auto cls, *classes)
    {
        classesData.append(cls->getSaveData());
    }
    foreach (auto relation, *relations)
    {
        relationsData.append(relation->getSaveData());
    }

    object.insert("classes", classesData);
    object.insert("relations", relationsData);
    return object;
}

void UMLData::addClass(UMLClassData *umlClassData)
{
    classes->insert(umlClassData);
    connect(umlClassData, &UMLClassData::modelChanged, this, &UMLData::classModelChanged);
    emit classModelAdded(umlClassData);
}

void UMLData::removeClass(UMLClassData *umlClassData)
{
    if (classes->remove(umlClassData))
    {
        emit classModelRemoved(umlClassData);
        delete umlClassData;
    }
}

void UMLData::addRelation(UMLRelationData *umlRelationData)
{
    relations->insert(umlRelationData);
    connect(umlRelationData, &UMLRelationData::modelChanged, this, &UMLData::relationModelChanged);
    emit relationModelAdded(umlRelationData);
}

void UMLData::removeRelation(UMLRelationData *umlRelationData)
{
    if (relations->remove(umlRelationData))
    {
        emit relationModelRemoved(umlRelationData);
        delete umlRelationData;
    }
}

void UMLData::addSequence(UMLSequenceData *umlSequenceData)
{
    sequences->insert(umlSequenceData);
    //connect(umlSequenceData, &UMLSequenceData::model)
    emit sequenceModelAdded(umlSequenceData);
}

void UMLData::removeSequence(UMLSequenceData* umlSequenceData)
{
    if (sequences->remove(umlSequenceData))
    {
        delete umlSequenceData;
    }
}

void UMLData::clearData()
{
    emit umlModelCleared();
    classes->clear();
    relations->clear();
}

UMLClassData* UMLData::findClassByName(QString className)
{
    foreach (UMLClassData *cls, *classes)
    {
        if (cls->getName() == className)
            return cls;
    }
    return nullptr;
}

QSet<UMLClassData *>* UMLData::getClasses()
{
    return classes;
}

QSet<UMLRelationData *> UMLData::getRelationsWithSourceClass(UMLClassData *umlClassData)
{
    QSet<UMLRelationData *> found;
    foreach (UMLRelationData *umlRelationData, *relations)
    {
        if (umlRelationData->getSource() == umlClassData)
        {
            found.insert(umlRelationData);
        }
    }
    return found;
}

// slots
void UMLData::classModelChanged(UMLClassData *umlClassData)
{
    emit classModelEdited(umlClassData);
}

void UMLData::relationModelChanged(UMLRelationData *umlRelationData)
{
    emit relationModelEdited(umlRelationData);
}
