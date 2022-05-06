#ifndef UMLSEQUENCEDATA_H
#define UMLSEQUENCEDATA_H

#include "data/data.h"
#include "data/umlcalldata.h"
#include "data/umlinstancedata.h"
#include "model/umlsequencemodel.h"

class UMLSequenceData : public Data<UMLSequenceModel>
{
public:
    virtual ~UMLSequenceData();
    bool load(QJsonObject object) override;
    void fromModel(UMLSequenceModel *model) override;
    UMLSequenceModel *toModel() override;

    QString getName() const;
    QList<UMLInstanceData *> getInstances() const;
    QList<UMLCallData *> getCalls() const;

private:
    QString name;
    QList<UMLInstanceData *> instances;
    QList<UMLCallData*> calls;

};

#endif // UMLSEQUENCEDATA_H
