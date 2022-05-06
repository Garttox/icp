#ifndef UMLINSTANCEDATA_H
#define UMLINSTANCEDATA_H

#include "data.h"
#include "model/umlinstancemodel.h"

class UMLInstanceData : public Data<UMLInstanceModel>
{
public:
    virtual ~UMLInstanceData() {};
    bool load(QJsonObject object) override;
    void fromModel(UMLInstanceModel *model) override;
    UMLInstanceModel *toModel() override;

    QString getName() const;
    QString getUmlClass() const;
    int getPosX() const;

private:
    QString name;
    QString umlClass;
    int posX;

};

#endif // UMLINSTANCEDATA_H
