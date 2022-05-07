/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlinstancedata.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLINSTANCEDATA_H
#define UMLINSTANCEDATA_H

#include "data.h"
#include "model/umlinstancemodel.h"

/**
 * @brief Data class for storing UML instance data.
 */
class UMLInstanceData : public Data<UMLInstanceModel>
{
public:
    virtual ~UMLInstanceData() {};
    bool load(QJsonObject object) override;
    void fromModel(UMLInstanceModel *model) override;
    QJsonObject toJson() const;
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
