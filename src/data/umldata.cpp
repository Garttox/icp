/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umldata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umldata.h"
#include "model/modelprovider.h"

UMLData::~UMLData()
{
    qDeleteAll(classes);
    qDeleteAll(relations);
    qDeleteAll(sequences);
}

bool UMLData::load(QJsonObject object)
{
    auto classes = fromJsonArray<UMLClassData>(object["classes"]);
    auto relations = fromJsonArray<UMLRelationData>(object["relations"]);
    auto sequences = fromJsonArray<UMLSequenceData>(object["sequences"]);

    if (!classes.ok || !relations.ok || !sequences.ok)
    {
        return false;
    }

    this->classes = classes.value;
    this->relations = relations.value;
    this->sequences = sequences.value;

    return true;
}

void UMLData::fromModel(UMLModel *model)
{
    this->classes = fromModels<UMLClassModel, UMLClassData>(model->getClasses());
    this->relations = fromModels<UMLRelationModel, UMLRelationData>(model->getRelations());
    this->sequences = fromModels<UMLSequenceModel, UMLSequenceData>(model->getSequences());
}

QJsonObject UMLData::toJson() const
{
    QJsonObject object;
    object.insert("classes", toJsonArray(classes));
    object.insert("relations", toJsonArray(relations));
    object.insert("sequences", toJsonArray(sequences));
    return object;
}

UMLModel *UMLData::toModel(void */*context*/)
{
    UMLModel* umlModel = ModelProvider::getInstance().getModel();

    QList<UMLClassModel*> umlClassModels = toModels<UMLClassData, UMLClassModel>(classes);
    foreach (auto umlClassModel, umlClassModels)
    {
        umlModel->addClass(umlClassModel);
    }

    QList<UMLRelationModel*> umlRelationModels = toModels<UMLRelationData, UMLRelationModel>(relations);
    foreach (auto umlRelationModel, umlRelationModels)
    {
        umlModel->addRelation(umlRelationModel);
    }

    QList<UMLSequenceModel*> umlSequenceModels = toModels<UMLSequenceData, UMLSequenceModel>(sequences);
    foreach (auto umlSequenceModel, umlSequenceModels)
    {
        umlModel->addSequence(umlSequenceModel);
    }

    return umlModel;
}

QList<UMLClassData *> UMLData::getClasses() const
{
    return classes;
}

QList<UMLRelationData *> UMLData::getRelations() const
{
    return relations;
}

QList<UMLSequenceData *> UMLData::getSequences() const
{
    return sequences;
}
