/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlparameterdata.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLPARAMETERDATA_H
#define UMLPARAMETERDATA_H

#include <QString>
#include "data/data.h"
#include "model/umlparametermodel.h"

/**
 * @brief Data class for storing parameter data.
 */
class UMLParameterData : Data<UMLParameterModel>
{
public:
    virtual ~UMLParameterData() {};
    bool load(QJsonObject object) override;
    void fromModel(UMLParameterModel *model) override;
    QJsonObject toJson() const;
    UMLParameterModel *toModel() override;

    QString getName() const;
    QString getType() const;

private:
    QString name;
    QString type;

};

#endif // UMLPARAMETERDATA_H
