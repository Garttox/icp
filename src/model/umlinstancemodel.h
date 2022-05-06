#ifndef UMLINSTANCEMODEL_H
#define UMLINSTANCEMODEL_H

#include "umlclassmodel.h"
#include <QString>

class UMLInstanceModel
{
public:
    UMLInstanceModel(QString name, UMLClassModel *umlClassModel, int posX);
    QString getDisplayName() const;
    QString getName() const;
    void setName(QString name);
    int getPosX() const;
    void setPosX(int posX);
    UMLClassModel* getClassModel();
private:
    QString name;
    UMLClassModel *umlClassModel;
    int posX;
};

#endif // UMLINSTANCEMODEL_H
