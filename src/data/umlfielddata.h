#ifndef UMLFIELDDATA_H
#define UMLFIELDDATA_H

#include "data/data.h"
#include "model/umlfieldmodel.h"
#include "umlattributedata.h"

class UMLFieldData : public UMLAttributeData, public Data<UMLFieldModel>
{
public:
    virtual ~UMLFieldData() {};
    bool load(QJsonObject object) override;
    void fromModel(UMLFieldModel *model) override;
    UMLFieldModel *toModel() override;

};

#endif // UMLFIELDDATA_H
