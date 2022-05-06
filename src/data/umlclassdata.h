#ifndef UMLCLASSDATA_H
#define UMLCLASSDATA_H

#include "data.h"
#include "data/umlfielddata.h"
#include "data/umlmethoddata.h"
#include "model/umlclassmodel.h"

class UMLClassData : Data<UMLClassModel>
{
public:
    virtual ~UMLClassData();
    bool load(QJsonObject object) override;
    void fromModel(UMLClassModel *model) override;
    UMLClassModel *toModel() override;

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
