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

QList<UMLClassModel *> UMLModel::getClasses() const
{
    return classes.values();
}

QList<UMLRelationModel *> UMLModel::getRelations() const
{
    return relations.values();
}

QList<UMLSequenceModel *> UMLModel::getSequences() const
{
    return sequences.values();
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
