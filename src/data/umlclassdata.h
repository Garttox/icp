/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlclassdata.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLCLASSDATA_H
#define UMLCLASSDATA_H

#include "data.h"
#include "data/umlfielddata.h"
#include "data/umlmethoddata.h"
#include "model/umlclassmodel.h"

/**
 * @brief Data class for holding UML class data.
 */
class UMLClassData : Data<UMLClassModel>
{
public:
    virtual ~UMLClassData();
    bool load(QJsonObject object) override;
    void fromModel(UMLClassModel *model) override;
    QJsonObject toJson() const;
    UMLClassModel *toModel(void* context = nullptr) override;

    QString getName() const;
    QString getType() const;
    int getPosX() const;
    int getPosY() const;
    QList<UMLFieldData *> getFields() const;
    QList<UMLMethodData *> getMethods() const;

private:
    QString name;
    QString type;
    int posX;
    int posY;
    QList<UMLFieldData*> fields;
    QList<UMLMethodData*> methods;

};

#endif // UMLCLASSDATA_H
