/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlcalldata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlcalldata.h"
#include "model/modelprovider.h"
#include "data.h"

bool UMLCallData::load(QJsonObject object)
{
    auto type = object.value("type");
    auto source =  object["source"];
    auto destination = object["destination"];
    auto method = object["method"];
    auto async = object["async"];
    auto duration = object["duration"];
    auto atTime = object["atTime"];

    if (hasNull(type, destination, method, async, duration, atTime))
    {
        return false;
    }

    this->type = type.toString();
    this->source = source.toString();
    this->destination = destination.toString();
    this->method = method.toString();
    this->async = async.toBool();
    this->duration = duration.toInt();
    this->atTime = atTime.toInt();

    return true;
}

void UMLCallData::fromModel(UMLCallModel *model)
{
    UMLInstanceModel *sourceInstance = model->getSource();
    this->type = model->getType().toString();
    this->source = sourceInstance != nullptr ? sourceInstance->getName() : nullptr;
    this->destination = model->getDestination()->getName();
    this->method = model->getMethod()->getName();
    this->async = model->getAsync();
    this->duration = model->getDuration();
    this->atTime = model->getAtTime();
}

QJsonObject UMLCallData::toJson() const
{
    QJsonObject object;
    object.insert("type", type);
    object.insert("source", source);
    object.insert("destination", destination);
    object.insert("method", method);
    object.insert("async", async);
    object.insert("duration", duration);
    object.insert("atTime", atTime);
    return object;
}

UMLCallModel *UMLCallData::toModel(UMLSequenceModel* context)
{
    UMLInstanceModel* srcInstanceModel = context->findInstanceByName(source);
    UMLInstanceModel* destInstanceModel = context->findInstanceByName(destination);
    UMLMethodModel* umlMethodModel = destInstanceModel->getClassModel()->findMethodByName(method);
    UMLCallType umlCallType(type);
    UMLCallModel* umlClassModel = new UMLCallModel(srcInstanceModel, destInstanceModel, umlMethodModel, async, duration, atTime, umlCallType);
    return umlClassModel;
}

QString UMLCallData::getType() const
{
    return type;
}

QString UMLCallData::getSource() const
{
    return source;
}

QString UMLCallData::getDestination() const
{
    return destination;
}

QString UMLCallData::getMethod() const
{
    return method;
}

bool UMLCallData::getAsync() const
{
    return async;
}

int UMLCallData::getDuration() const
{
    return duration;
}

int UMLCallData::getAtTime() const
{
    return atTime;
}
