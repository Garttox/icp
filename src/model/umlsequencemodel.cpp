#include "modelprovider.h"
#include "umlsequencemodel.h"

#include <QJsonObject>
#include <QJsonArray>

UMLSequenceModel::UMLSequenceModel(QString name) :
    name(name)
{}

UMLSequenceModel::~UMLSequenceModel()
{
    qDeleteAll(this->instances.begin(), this->instances.end());
    qDeleteAll(this->calls.begin(), this->calls.end());
}

bool UMLSequenceModel::loadData(QJsonObject jsonSequenceData)
{
    UMLModel *umlModel = ModelProvider::getInstance().getModel();
    //read instances
    foreach (auto instanceEl, jsonSequenceData["instances"].toArray())
    {
        QJsonObject object = instanceEl.toObject();
        if (object["name"].isNull() || object["className"].isNull() || object["posX"].isNull())
        {
            return false;
        }
        QString name = object["name"].toString();
        UMLClassModel *umlClassModel = umlModel->findClassByName(object["className"].toString());
        int posX = object["posX"].toInt();
        UMLInstanceModel *instanceModel = new UMLInstanceModel(name, umlClassModel, posX);
        addInstance(instanceModel);
    }

    //read calls
    foreach (auto callsEl, jsonSequenceData["calls"].toArray())
    {
        QJsonObject object = callsEl.toObject();
        if (object["destination"].isNull() || object["method"].isNull() || object["async"].isNull() ||
                object["duration"].isNull() || object["atTime"].isNull() || object["type"].isNull())
        {
            return false;
        }
        UMLInstanceModel *source;
        if (object["source"].isNull())
        {
            source = nullptr;
        }
        else
        {
            source = findInstanceByName(object["source"].toString());
        }

        UMLInstanceModel *destination = findInstanceByName(object["destination"].toString());
        UMLMethodModel *method = destination->getClassModel()->findMethodByName(object["method"].toString());
        bool async = object["async"].toBool();
        int duration = object["duration"].toInt();
        int atTime = object["atTime"].toInt();
        UMLCallType type = UMLCallType(object["type"].toString());
        UMLCallModel *call = new UMLCallModel(source, destination, method, async, duration, atTime, type);
        addCall(call);
    }
    return true;
}

void UMLSequenceModel::addInstance(UMLInstanceModel *instance)
{
    this->instances.insert(instance);
    emit instanceModelAdded(instance);
}

void UMLSequenceModel::addCall(UMLCallModel *call)
{
    this->calls.insert(call);
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
