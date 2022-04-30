#include "umlrelationdata.h"

UMLRelationData::UMLRelationData(UMLClassData *src, UMLClassData *dest, UMLRelationType type, int srcAnchorId, int destAnchorId)
    : source(src), destination(dest), type(type), sourceAnchorId(srcAnchorId), destinationAnchorId(destAnchorId)
{}

UMLClassData *UMLRelationData::getSource() const
{
    return source;
}

UMLClassData *UMLRelationData::getDestination() const
{
    return destination;
}

UMLRelationType UMLRelationData::getType() const
{
    return type;
}

int UMLRelationData::getSourceAnchorId() const
{
    return sourceAnchorId;
}

int UMLRelationData::getDestinationAnchorId() const
{
    return destinationAnchorId;
}

QJsonObject UMLRelationData::getSaveData()
{
    QJsonObject object;
    object.insert("type", type.toString());
    object.insert("source", source->getName());
    object.insert("destination", destination->getName());
    object.insert("sourceAnchorId", sourceAnchorId);
    object.insert("destinationAnchorId", destinationAnchorId);
    return object;
}

void UMLRelationData::setType(UMLRelationType type)
{
    this->type = type;
    emit modelChanged(this);
}
