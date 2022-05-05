#include "dataprovider.h"
#include "umlsequencedata.h"

#include <QJsonObject>
#include <QJsonArray>

UMLSequenceData::UMLSequenceData(QString name) :
    name(name)
{}

UMLSequenceData::~UMLSequenceData()
{
    qDeleteAll(this->instances.begin(), this->instances.end());
    qDeleteAll(this->calls.begin(), this->calls.end());
}

bool UMLSequenceData::loadData(QJsonObject jsonSequenceData)
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    //read instances
    foreach (auto instanceEl, jsonSequenceData["instances"].toArray())
    {
        QJsonObject object = instanceEl.toObject();
        if (object["name"].isNull() || object["className"].isNull() || object["posX"].isNull())
        {
            return false;
        }
        QString name = object["name"].toString();
        UMLClassData *umlClassData = umlData->findClassByName(object["className"].toString());
        int posX = object["posX"].toInt();
        UMLInstanceData *instanceData = new UMLInstanceData(name, umlClassData, posX);
        addInstance(instanceData);
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
        UMLInstanceData *source;
        if (object["source"].isNull())
        {
            source = nullptr;
        }
        else
        {
            source = findInstanceByName(object["source"].toString());
        }

        UMLInstanceData *destination = findInstanceByName(object["destination"].toString());
        UMLMethodData *method = destination->getClassData()->findMethodByName(object["method"].toString());
        bool async = object["async"].toBool();
        int duration = object["duration"].toInt();
        int atTime = object["atTime"].toInt();
        UMLCallType type = UMLCallType(object["type"].toString());
        UMLCallData *callData = new UMLCallData(source, destination, method, async, duration, atTime, type);
        addCall(callData);
    }
    return true;
}

void UMLSequenceData::addInstance(UMLInstanceData *instance)
{
    this->instances.insert(instance);
    emit instanceModelAdded(instance);
}

void UMLSequenceData::addCall(UMLCallData *call)
{
    this->calls.insert(call);
}

UMLInstanceData* UMLSequenceData::findInstanceByName(QString instanceName)
{
    foreach (UMLInstanceData *instance, instances)
    {
        if (instance->getName() == instanceName)
            return instance;
    }
    return nullptr;
}

QString UMLSequenceData::getName()
{
    return this->name;
}
