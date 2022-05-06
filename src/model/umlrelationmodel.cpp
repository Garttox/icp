#include "umlrelationmodel.h"

UMLRelationModel::UMLRelationModel(UMLClassModel *src, UMLClassModel *dest, UMLRelationType type, int srcAnchorId, int destAnchorId)
    : source(src), destination(dest), type(type), sourceAnchorId(srcAnchorId), destinationAnchorId(destAnchorId)
{}

UMLClassModel *UMLRelationModel::getSource() const
{
    return source;
}

UMLClassModel *UMLRelationModel::getDestination() const
{
    return destination;
}

UMLRelationType UMLRelationModel::getType() const
{
    return type;
}

int UMLRelationModel::getSourceAnchorId() const
{
    return sourceAnchorId;
}

int UMLRelationModel::getDestinationAnchorId() const
{
    return destinationAnchorId;
}

QJsonObject UMLRelationModel::getSaveData()
{
    QJsonObject object;
    object.insert("type", type.toString());
    object.insert("source", source->getName());
    object.insert("destination", destination->getName());
    object.insert("sourceAnchorId", sourceAnchorId);
    object.insert("destinationAnchorId", destinationAnchorId);
    return object;
}

void UMLRelationModel::setType(UMLRelationType type)
{
    this->type = type;
    emit modelChanged(this);
}
