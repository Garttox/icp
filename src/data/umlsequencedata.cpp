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
    this->calls = fromModels<UMLCallModel, UMLCallData>(model->getCalls());
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
    UMLSequenceModel *umlSequenceModel = new UMLSequenceModel(name, QSet<UMLInstanceModel*>(), QSet<UMLCallModel*>());
    QList<UMLInstanceModel*> instanceModels = toModels<UMLInstanceData, UMLInstanceModel>(instances);
    foreach (auto instanceModel, instanceModels)
    {
        umlSequenceModel->addInstance(instanceModel);
    }

    QList<UMLCallModel*> callModels = toModels<UMLCallData, UMLCallModel>(calls, umlSequenceModel);
    foreach (auto callModel, callModels)
    {
        umlSequenceModel->addCall(callModel);
    }
    return umlSequenceModel;
}

void UMLSequenceData::setName(QString name)
{
    this->name = name;
}

void UMLSequenceData::addInstance(UMLInstanceData *instance)
{
    this->instances.append(instance);
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

QStringList UMLSequenceData::getInstanceNames() const
{
    QStringList list;
    foreach (auto instance, instances)
    {
        list.append(instance->getName());
    }
    return list;
}

UMLInstanceData *UMLSequenceData::getInstanceByName(QString name) const
{
    foreach (auto instance, instances)
    {
        if (instance->getName() == name)
        {
            return instance;
        }
    }
    return nullptr;
}
