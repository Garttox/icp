/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlsequencedata.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLSEQUENCEDATA_H
#define UMLSEQUENCEDATA_H

#include "data/data.h"
#include "data/umlcalldata.h"
#include "data/umlinstancedata.h"
#include "model/umlsequencemodel.h"

/**
 * @brief Data class for storing sequence diagram data.
 */
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
