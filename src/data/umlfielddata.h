/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlfielddata.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLFIELDDATA_H
#define UMLFIELDDATA_H

#include "data/data.h"
#include "model/umlfieldmodel.h"
#include "umlattributedata.h"

/**
 * @brief Data class for holding class's field data.
 */
class UMLFieldData : public UMLAttributeData, public Data<UMLFieldModel>
{
public:
    virtual ~UMLFieldData() {};
    bool load(QJsonObject object) override;
    void fromModel(UMLFieldModel *model) override;
    QJsonObject toJson() const;
    UMLFieldModel *toModel(void* context = nullptr) override;

};

#endif // UMLFIELDDATA_H
