#ifndef UMLSEQUENCEDATA_H
#define UMLSEQUENCEDATA_H

#include "umlcalldata.h"
#include "umlinstancedata.h"

#include <QString>



class UMLSequenceData
{
public:
    UMLSequenceData(QString name);
    ~UMLSequenceData();
    bool loadData(QJsonObject jsonSequenceData);
    void addInstance(UMLInstanceData *instance);
    void addCall(UMLCallData *call);
    UMLInstanceData* findInstanceByName(QString instanceName);
    QString getName();
private:
    QString name;
    QSet<UMLInstanceData *> instances;
    QSet<UMLCallData *> calls;
};

#endif // UMLSEQUENCEDATA_H
