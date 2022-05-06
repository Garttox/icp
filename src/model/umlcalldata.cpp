#include "umlcalldata.h"

UMLCallData::UMLCallData(UMLInstanceData *source, UMLInstanceData *destination, UMLMethodData *method, bool async, int duration, int atTime, UMLCallType type) :
    source(source), destination(destination), method(method), async(async), duration(duration), atTime(atTime), type(type)
{}

UMLInstanceData *UMLCallData::getDestination() const
{
    return this->destination;
}

UMLInstanceData *UMLCallData::getSource() const
{
    return this->source;
}

UMLCallType UMLCallData::getType() const
{
    return this->type;
}

int UMLCallData::getAtTime() const
{
    return this->atTime;
}
