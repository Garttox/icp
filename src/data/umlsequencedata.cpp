/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlsequencedata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlsequencedata.h"

UMLSequenceData::~UMLSequenceData()
{
    qDeleteAll(instances);
    qDeleteAll(calls);
}

bool UMLSequenceData::load(QJsonObject object)
{
    auto name = object["name"];
    auto instances = fromJsonArray<UMLInstanceData>(object["instances"]);
    auto calls = fromJsonArray<UMLCallData>(object["calls"]);

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
    this->name = model->getName();
    this->instances = fromModels<UMLInstanceModel, UMLInstanceData>(model->getInstances());
    // FIXME: this->calls = fromModels<UMLCallModel, UMLCallData>(model->getCalls());
}

QJsonObject UMLSequenceData::toJson() const
{
    QJsonObject object;
    object.insert("name", name);
    object.insert("instances", toJsonArray(instances));
    object.insert("calls", toJsonArray(calls));
    return object;
}

UMLSequenceModel *UMLSequenceData::toModel(void */*context*/)
{
    QList<UMLInstanceModel*> instanceModels = toModels<UMLInstanceData, UMLInstanceModel>(instances);
    UMLSequenceModel *umlSequenceModel = new UMLSequenceModel(name, instanceModels, QList<UMLCallModel*>());
    QList<UMLCallModel*> callModels = toModels<UMLCallData, UMLCallModel>(calls, umlSequenceModel);

    foreach (auto callModel, callModels)
    {
        umlSequenceModel->addCall(callModel);
    }
    return umlSequenceModel;
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
