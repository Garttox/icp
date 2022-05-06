/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umlmodel.cpp
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#include <QJsonObject>
#include <QJsonArray>

#include "umlmodel.h"

UMLModel::UMLModel()
{}

UMLModel::~UMLModel()
{
    qDeleteAll(classes.begin(), classes.end());
    qDeleteAll(relations.begin(), relations.end());
}

bool UMLModel::loadData(QJsonObject json)
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
        UMLClassModel *umlClassModel = new UMLClassModel(name, type, posX, posY);
        bool loadedSuccesfully = umlClassModel->loadData(object);
        if (!loadedSuccesfully)
        {
            delete umlClassModel;
            return false;
        }
        addClass(umlClassModel);
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

        UMLClassModel *source = findClassByName(object["source"].toString());
        UMLClassModel *destination = findClassByName(object["destination"].toString());
        UMLRelationType type(object["type"].toString());
        int sourceAnchorId = object["sourceAnchorId"].toInt();
        int destinationAnchorId = object["destinationAnchorId"].toInt();
        UMLRelationModel *relation = new UMLRelationModel(source, destination, type, sourceAnchorId, destinationAnchorId);
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
        UMLSequenceModel *umlSequenceModel = new UMLSequenceModel(name);
        addSequence(umlSequenceModel);
        bool loadedSuccesfully = umlSequenceModel->loadData(object);
        if (!loadedSuccesfully)
        {
            removeSequence(umlSequenceModel);
            return false;
        }
    }
    return true;
}

QJsonObject UMLModel::getSaveData()
{
    QJsonObject object;
    QJsonArray classesData;
    QJsonArray relationsData;

    foreach (auto cls, classes)
    {
        classesData.append(cls->getSaveData());
    }
    foreach (auto relation, relations)
    {
        relationsData.append(relation->getSaveData());
    }

    object.insert("classes", classesData);
    object.insert("relations", relationsData);
    return object;
}

void UMLModel::addClass(UMLClassModel *umlClassModel)
{
    classes.insert(umlClassModel);
    connect(umlClassModel, &UMLClassModel::modelChanged, this, &UMLModel::classModelChanged);
    emit classModelAdded(umlClassModel);
}

void UMLModel::removeClass(UMLClassModel *umlClassModel)
{
    if (classes.remove(umlClassModel))
    {
        emit classModelRemoved(umlClassModel);
        delete umlClassModel;
    }
}

void UMLModel::addRelation(UMLRelationModel *umlRelationModel)
{
    relations.insert(umlRelationModel);
    connect(umlRelationModel, &UMLRelationModel::modelChanged, this, &UMLModel::relationModelChanged);
    emit relationModelAdded(umlRelationModel);
}

void UMLModel::removeRelation(UMLRelationModel *umlRelationModel)
{
    if (relations.remove(umlRelationModel))
    {
        emit relationModelRemoved(umlRelationModel);
        delete umlRelationModel;
    }
}

void UMLModel::addSequence(UMLSequenceModel *umlSequenceModel)
{
    sequences.insert(umlSequenceModel);
    //connect(umlSequenceModel, &UMLSequenceData::model)
    emit sequenceModelAdded(umlSequenceModel);
}

void UMLModel::removeSequence(UMLSequenceModel* umlSequenceModel)
{
    if (sequences.remove(umlSequenceModel))
    {
        delete umlSequenceModel;
    }
}

void UMLModel::clear()
{
    emit umlModelCleared();
    classes.clear();
    relations.clear();
}

UMLClassModel* UMLModel::findClassByName(QString className)
{
    foreach (UMLClassModel *cls, classes)
    {
        if (cls->getName() == className)
            return cls;
    }
    return nullptr;
}

QSet<UMLClassModel *> UMLModel::getClasses()
{
    return classes;
}

QSet<UMLRelationModel *> UMLModel::getRelationsWithSourceClass(UMLClassModel *umlClassModel)
{
    QSet<UMLRelationModel *> found;
    foreach (UMLRelationModel *umlRelationModel, relations)
    {
        if (umlRelationModel->getSource() == umlClassModel)
        {
            found.insert(umlRelationModel);
        }
    }
    return found;
}

// slots
void UMLModel::classModelChanged(UMLClassModel *umlClassModel)
{
    emit classModelEdited(umlClassModel);
}

void UMLModel::relationModelChanged(UMLRelationModel *umlRelationModel)
{
    emit relationModelEdited(umlRelationModel);
}
