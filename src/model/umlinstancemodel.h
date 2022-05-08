#ifndef UMLINSTANCEMODEL_H
#define UMLINSTANCEMODEL_H

#include "umlclassmodel.h"
#include <QString>

class UMLInstanceModel : public QObject
{
    Q_OBJECT
public:
    UMLInstanceModel(QString name, UMLClassModel *umlClassModel, int posX, int posY);
    QString getDisplayName() const;
    QString getName() const;
    void setName(QString name);
    int getPosX() const;
    void setPosX(int posX);
    int getPosY() const;
    void setPosY(int posY);
    UMLClassModel* getClassModel();

signals:
    void modelChanged(UMLInstanceModel *umlInstanceModel);

private:
    QString name;
    UMLClassModel *umlClassModel;
    int posX;
    int posY;

};

#endif // UMLINSTANCEMODEL_H
