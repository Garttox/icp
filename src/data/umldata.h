/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umldata.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLDATA_H
#define UMLDATA_H

#include "data.h"
#include "data/umlclassdata.h"
#include "data/umlrelationdata.h"
#include "data/umlsequencedata.h"
#include "model/umlmodel.h"

/**
 * @brief Data class for storing whole application data model.
 */
class UMLData : Data<UMLModel>
{
public:
    virtual ~UMLData();
    bool load(QJsonObject object) override;
    void fromModel(UMLModel *model) override;
    QJsonObject toJson() const;
    UMLModel *toModel(void* context = nullptr) override;

    QList<UMLClassData *> getClasses() const;
    QList<UMLRelationData *> getRelations() const;
    QList<UMLSequenceData *> getSequences() const;

private:
    QList<UMLClassData *> classes;
    QList<UMLRelationData *> relations;
    QList<UMLSequenceData *> sequences;

};

#endif // UMLDATA_H
