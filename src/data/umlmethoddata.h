#ifndef UMLMETHODDATA_H
#define UMLMETHODDATA_H

#include "umlattributedata.h"
#include "model/umlmethodmodel.h"
#include "data/umlparameterdata.h"
#include "data/data.h"

class UMLMethodData : public UMLAttributeData, public Data<UMLMethodModel>
{
public:
    virtual ~UMLMethodData();
    bool load(QJsonObject object) override;
    void fromModel(UMLMethodModel *model) override;
    UMLMethodModel *toModel() override;

    QList<UMLParameterData *> getParameters() const;

private:
    QList<UMLParameterData *> parameters;

};

#endif // UMLMETHODDATA_H
