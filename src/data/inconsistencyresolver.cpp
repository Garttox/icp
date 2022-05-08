#include "inconsistencyresolver.h"

InconsistencyResolver::InconsistencyResolver()
{}

QStringList InconsistencyResolver::resolve(UMLData *umlData)
{
    resolved.clear();

    resolveDuplicatedSequenceNames(umlData);
    // resolveDuplicatedClassNames
    resolveNonExistingInstancesForCalls(umlData);
    resolveNonExistingMethodsForCalls(umlData);
    resolveNonExistingClassesForInstances(umlData);

    return resolved;
}

void InconsistencyResolver::resolveDuplicatedSequenceNames(UMLData *umlData)
{
    QStringList encountered;
    do {
        encountered.clear();
        foreach (auto umlSequenceData, umlData->getSequences())
        {
            QString name = umlSequenceData->getName();
            if (encountered.contains(name))
            {
                name.append('*');
                umlSequenceData->setName(name);
                resolved.append(QString("Sequence diagram renamed to '%1', due to duplication of names.").arg(name));
            }
            encountered.append(name);
        }
    } while (hasDuplicate(encountered));
}

void InconsistencyResolver::resolveNonExistingMethodsForCalls(UMLData *umlData)
{
    foreach (auto umlSequenceData, umlData->getSequences())
    {
        foreach (auto umlCallData, umlSequenceData->getCalls())
        {
            QString methodName = umlCallData->getMethod();
            QString destination = umlCallData->getDestination();
            UMLInstanceData *instance = umlSequenceData->getInstanceByName(destination);
            UMLClassData *umlClass = umlData->getClassByName(instance->getUmlClass());

            if (!umlClass->hasMethodWithName(methodName))
            {
                UMLMethodData *newMethod = new UMLMethodData(methodName, "", "Public");
                umlClass->addMethod(newMethod);
                resolved.append(QString("Added method '%1' from call, because it was not present in '%2'.").arg(methodName, umlClass->getName()));
            }
        }
    }
}

void InconsistencyResolver::resolveNonExistingInstancesForCalls(UMLData *umlData)
{
    foreach (auto umlSequenceData, umlData->getSequences())
    {
        foreach (auto umlCallData, umlSequenceData->getCalls())
        {
            QStringList instanceNames = umlSequenceData->getInstanceNames();
            QString source = umlCallData->getSource();
            QString destination = umlCallData->getDestination();
            if (!instanceNames.contains(destination))
            {
                UMLInstanceData *newInstance = new UMLInstanceData(destination, "(UNKNOWN)");
                umlSequenceData->addInstance(newInstance);
                resolved.append(QString("Added instance '%1' from call, because it was not present in sequence.").arg(destination, destination));
            }
            if (source != nullptr && source != destination && !instanceNames.contains(source))
            {
                UMLInstanceData *newInstance = new UMLInstanceData(source, "(UNKNOWN)");
                umlSequenceData->addInstance(newInstance);
                resolved.append(QString("Added instance '%1' from call, because it was not present in sequence.").arg(destination, source));
            }
        }
    }
}

void InconsistencyResolver::resolveNonExistingClassesForInstances(UMLData *umlData)
{
    foreach (auto umlSequenceData, umlData->getSequences())
    {
        foreach (auto umlInstanceData, umlSequenceData->getInstances())
        {
            QString className = umlInstanceData->getUmlClass();
            QStringList classNames = umlData->getClassNames();
            if (!classNames.contains(className))
            {
                QString instanceName = umlInstanceData->getName();
                umlData->addClass(new UMLClassData(className));
                resolved.append(QString("Class '1%' added, as it was referenced in instance '%2'.").arg(className, instanceName));
            }
        }
    }
}

bool InconsistencyResolver::hasDuplicate(QStringList list)
{
    QStringList encountered;
    foreach (auto item, list)
    {
        if (encountered.contains(item))
        {
            return true;
        }
        encountered.append(item);
    }
    return false;
}
