/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlrelationdata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlrelationdata.h"
#include "model/modelprovider.h"

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
    this->type = model->getType().toString();
    this->source = model->getSource()->getName();
    this->destination = model->getDestination()->getName();
    this->sourceAnchorId = model->getSourceAnchorId();
    this->destinationAnchorId = model->getDestinationAnchorId();
}

QJsonObject UMLRelationData::toJson() const
{
    QJsonObject object;
    object.insert("type", type);
    object.insert("source", source);
    object.insert("destination", destination);
    object.insert("sourceAnchorId", sourceAnchorId);
    object.insert("destinationAnchorId", destinationAnchorId);
    return object;
}

UMLRelationModel *UMLRelationData::toModel(void */*context*/)
{
    UMLModel* model = ModelProvider::getInstance().getModel();
    UMLClassModel* srcClassModel = model->findClassByName(source);
    UMLClassModel* destClassModel = model->findClassByName(destination);
    UMLRelationType umlRelationType(type);
    UMLRelationModel *umlRelationModel = new UMLRelationModel(srcClassModel, destClassModel, umlRelationType, sourceAnchorId, destinationAnchorId);
    return umlRelationModel;
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
