#ifndef UMLINSTANCEDATA_H
#define UMLINSTANCEDATA_H

#include "umlclassdata.h"

#include <QString>



class UMLInstanceData
{
public:
    UMLInstanceData(QString name, UMLClassData *umlClassData, int posX);
    QString getDisplayName() const;
    QString getName() const;
    void setName(QString name);
    int getPosX() const;
    void setPosX(int posX);
    UMLClassData* getClassData();
private:
    QString name;
    UMLClassData *umlClassData;
    int posX;
};

#endif // UMLINSTANCEDATA_H
