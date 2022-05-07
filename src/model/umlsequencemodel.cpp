#include "modelprovider.h"
#include "umlsequencemodel.h"

#include <QJsonObject>
#include <QJsonArray>

UMLSequenceModel::UMLSequenceModel(QString name) :
    name(name)
{}

UMLSequenceModel::UMLSequenceModel(QString name, QList<UMLInstanceModel *> instances, QList<UMLCallModel *> calls) :
    name(name), instances(instances), calls(calls)
{}

UMLSequenceModel::~UMLSequenceModel()
{
    qDeleteAll(this->instances.begin(), this->instances.end());
    qDeleteAll(this->calls.begin(), this->calls.end());
}

void UMLSequenceModel::addInstance(UMLInstanceModel *instance)
{
    this->instances.append(instance);
    emit instanceModelAdded(instance);
}

void UMLSequenceModel::addCall(UMLCallModel *call)
{
    this->calls.insert(call);
    emit callModelAdded(call);
}

UMLInstanceModel* UMLSequenceModel::findInstanceByName(QString instanceName)
{
    foreach (UMLInstanceModel *instance, instances)
    {
        if (instance->getName() == instanceName)
            return instance;
    }
    return nullptr;
}

QString UMLSequenceModel::getName()
{
    return this->name;
}

UMLCallModel *UMLSequenceModel::instanceCreatedBy(UMLInstanceModel *umlInstanceModel)
{
    foreach(auto call, calls)
    {
        if (call->getDestination() == umlInstanceModel && call->getType() == UMLCallType::CREATE)
        {
            return call;
        }
    }
    return nullptr;
}

UMLCallModel *UMLSequenceModel::instanceDestroyedBy(UMLInstanceModel *umlInstanceModel)
{
    foreach(auto call, calls)
    {
        if (call->getDestination() == umlInstanceModel && call->getType() == UMLCallType::DESTROY)
        {
            return call;
        }
    }
    return nullptr;
}

QList<UMLInstanceModel *> UMLSequenceModel::getInstances() const
{
    return instances;
}

QList<UMLCallModel *> UMLSequenceModel::getCalls() const
{
    return calls;
}
