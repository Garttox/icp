/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umldata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umldata.h"

UMLData::~UMLData()
{
    qDeleteAll(classes);
    qDeleteAll(relations);
    qDeleteAll(sequences);
}

bool UMLData::load(QJsonObject object)
{
    auto classes = loadArray<UMLClassData>(object["classes"]);
    auto relations = loadArray<UMLRelationData>(object["relations"]);
    auto sequences = loadArray<UMLSequenceData>(object["sequences"]);

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
    // TODO
}

UMLModel *UMLData::toModel()
{
    // TODO
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
