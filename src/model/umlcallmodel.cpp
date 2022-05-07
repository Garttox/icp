#include "umlcallmodel.h"

UMLCallModel::UMLCallModel(UMLInstanceModel *source, UMLInstanceModel *destination, UMLMethodModel *method, bool async, int duration, int atTime, UMLCallType type) :
    source(source), destination(destination), method(method), async(async), duration(duration), atTime(atTime), type(type)
{}

UMLInstanceModel *UMLCallModel::getSource() const
{
    return source;
}

UMLInstanceModel *UMLCallModel::getDestination() const
{
    return destination;
}

UMLMethodModel *UMLCallModel::getMethod() const
{
    return method;
}

bool UMLCallModel::getAsync() const
{
    return async;
}

int UMLCallModel::getDuration() const
{
    return duration;
}

int UMLCallModel::getAtTime() const
{
    return atTime;
}

UMLCallType UMLCallModel::getType() const
{
    return type;
}
