#include "umlcallmodel.h"

UMLCallModel::UMLCallModel(UMLInstanceModel *source, UMLInstanceModel *destination, UMLMethodModel *method, bool async, int duration, int atTime, UMLCallType type) :
    source(source), destination(destination), method(method), async(async), duration(duration), atTime(atTime), type(type)
{}

UMLInstanceModel *UMLCallModel::getDestination() const
{
    return this->destination;
}

UMLInstanceModel *UMLCallModel::getSource() const
{
    return this->source;
}

UMLCallType UMLCallModel::getType() const
{
    return this->type;
}

int UMLCallModel::getAtTime() const
{
    return this->atTime;
}
