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

void UMLRelationModel::setType(UMLRelationType type)
{
    this->type = type;
    emit modelChanged(this);
}
