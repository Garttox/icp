#include "umlsequencedata.h"

UMLSequenceData::~UMLSequenceData()
{
    qDeleteAll(instances);
    qDeleteAll(calls);
}

bool UMLSequenceData::load(QJsonObject object)
{
    auto name = object["name"];
    auto instances = loadArray<UMLInstanceData>(object["source"]);
    auto calls = loadArray<UMLCallData>(object["calls"]);

    if (hasNull(name) || !instances.ok || !calls.ok)
    {
        return false;
    }

    this->name = name.toString();
    this->instances = instances.value;
    this->calls = calls.value;

    return true;
}

void UMLSequenceData::fromModel(UMLSequenceModel *model)
{
    // TODO
}

UMLSequenceModel *UMLSequenceData::toModel()
{
    // TODO
}

QString UMLSequenceData::getName() const
{
    return name;
}

QList<UMLInstanceData *> UMLSequenceData::getInstances() const
{
    return instances;
}

QList<UMLCallData *> UMLSequenceData::getCalls() const
{
    return calls;
}
