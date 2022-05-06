/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlrelationdata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlrelationdata.h"

bool UMLRelationData::load(QJsonObject object)
{
    auto type = object["type"];
    auto source =  object["source"];
    auto destination = object["destination"];
    auto sourceAnchorId = object["sourceAnchorId"];
    auto destinationAnchorId = object["destinationAnchorId"];

    if (hasNull(type, source, destination, sourceAnchorId, destinationAnchorId))
    {
        return false;
    }

    this->type = type.toString();
    this->source = source.toString();
    this->destination = destination.toString();
    this->sourceAnchorId = sourceAnchorId.toInt();
    this->destinationAnchorId = destinationAnchorId.toInt();

    return true;
}

void UMLRelationData::fromModel(UMLRelationModel *model)
{
    // TODO
}

UMLRelationModel *UMLRelationData::toModel()
{
    // TODO
}

QString UMLRelationData::getSource() const
{
    return source;
}

QString UMLRelationData::getDestination() const
{
    return destination;
}

QString UMLRelationData::getType() const
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
