#include "modelprovider.h"
#include "umlsequencemodel.h"

#include <QJsonObject>
#include <QJsonArray>

UMLSequenceModel::UMLSequenceModel(QString name) :
    name(name)
{}

UMLSequenceModel::UMLSequenceModel(QString name, QSet<UMLInstanceModel *> instances, QSet<UMLCallModel *> calls) :
    name(name), instances(instances), calls(calls)
{}

UMLSequenceModel::~UMLSequenceModel()
{
    qDeleteAll(this->instances.begin(), this->instances.end());
    qDeleteAll(this->calls.begin(), this->calls.end());
}

void UMLSequenceModel::addInstance(UMLInstanceModel *umlInstanceModel)
{
    this->instances.insert(umlInstanceModel);
    connect(umlInstanceModel, &UMLInstanceModel::modelChanged, this, &UMLSequenceModel::instanceModelChanged);
    emit instanceModelAdded(umlInstanceModel);
}

void UMLSequenceModel::removeInstance(UMLInstanceModel *umlInstanceModel)
{
    if (instances.remove(umlInstanceModel))
    {
        foreach(auto call, calls)
        {
            if (call->getDestination() == umlInstanceModel || call->getSource() == umlInstanceModel)
            {
                removeCall(call);
            }
        }
        emit instanceModelRemoved(umlInstanceModel);
        delete umlInstanceModel;
    }
}

void UMLSequenceModel::addCall(UMLCallModel *umlCallModel)
{
    this->calls.insert(umlCallModel);
    connect(umlCallModel, &UMLCallModel::modelChanged, this, &UMLSequenceModel::callModelChanged);
    emit callModelAdded(umlCallModel);
}

void UMLSequenceModel::removeCall(UMLCallModel *umlCallModel)
{
    if (calls.remove(umlCallModel))
    {
        emit callModelRemoved(umlCallModel);
        delete umlCallModel;
    }
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
    return instances.values();
}

QList<UMLCallModel *> UMLSequenceModel::getCalls() const
{
    return calls.values();
}

// - - - - - private slots  - - - - -

void UMLSequenceModel::instanceModelChanged(UMLInstanceModel *umlInstanceModel)
{
    emit instanceModelEdited(umlInstanceModel);
}

void UMLSequenceModel::callModelChanged(UMLCallModel *umlCallModel)
{
    emit callModelEdited(umlCallModel);
}
