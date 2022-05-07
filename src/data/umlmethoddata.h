/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlmethoddata.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLMETHODDATA_H
#define UMLMETHODDATA_H

#include "umlattributedata.h"
#include "model/umlmethodmodel.h"
#include "data/umlparameterdata.h"
#include "data/data.h"

/**
 * @brief Data class for storing class's method data.
 */
class UMLMethodData : public UMLAttributeData, public Data<UMLMethodModel>
{
public:
    virtual ~UMLMethodData();
    bool load(QJsonObject object) override;
    void fromModel(UMLMethodModel *model) override;
    QJsonObject toJson() const;
    UMLMethodModel *toModel() override;

    QList<UMLParameterData *> getParameters() const;

private:
    QList<UMLParameterData *> parameters;

};

#endif // UMLMETHODDATA_H
