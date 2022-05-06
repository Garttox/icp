#ifndef UMLPARAMETERDATA_H
#define UMLPARAMETERDATA_H

#include <QString>
#include "data/data.h"
#include "model/umlparametermodel.h"

class UMLParameterData : Data<UMLParameterModel>
{

public:
    virtual ~UMLParameterData() {};
    bool load(QJsonObject object) override;
    void fromModel(UMLParameterModel *model) override;
    UMLParameterModel *toModel() override;

    QString getName() const;
    QString getType() const;

private:
    QString name;
    QString type;

};

#endif // UMLPARAMETERDATA_H
