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

bool UMLData::loadData(QJsonObject json)
{
    // read classes
    foreach (auto clsEl, json["classes"].toArray())
    {
        if (clsEl.toObject()["name"].isNull() || clsEl.toObject()["type"].isNull() ||
                clsEl.toObject()["posX"].isNull() || clsEl.toObject()["posY"].isNull())
        {
            return false;
        }

        QString name = clsEl.toObject()["name"].toString();
        UMLClassType type = UMLClassType(clsEl.toObject()["type"].toString());
        int posX = clsEl.toObject()["posX"].toInt();
        int posY = clsEl.toObject()["posY"].toInt();
        UMLClassData *classData = new UMLClassData(name, type, posX, posY);
        bool loadedSuccesfully = classData->loadData(clsEl.toObject());
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

void UMLData::addClass(UMLClassData *classData)
{
    classes->insert(classData);
    connect(classData, &UMLClassData::modelChanged, this, &UMLData::classModelChanged);
    emit classModelAdded(classData);
}

void UMLData::removeClass(UMLClassData *classData)
{
    if (classes->remove(classData))
    {
        // emit classModelRemoved(umlRelationData);
        delete classData;
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
