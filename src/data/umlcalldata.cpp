/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlcalldata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlcalldata.h"
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
    // TODO
}

UMLCallModel *UMLCallData::toModel()
{
    // TODO
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
