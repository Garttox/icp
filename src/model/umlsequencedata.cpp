#include "umlsequencedata.h"

UMLSequenceData::UMLSequenceData(QString name) :
    name(name)
{}

UMLSequenceData::~UMLSequenceData()
{
    qDeleteAll(this->instances.begin(), this->instances.end());
    qDeleteAll(this->calls.begin(), this->calls.end());
}

void UMLSequenceData::addInstance(UMLInstanceData *instance)
{
    this->instances.insert(instance);
}

void UMLSequenceData::addCall(UMLCallData *call)
{
    this->calls.insert(call);
}
