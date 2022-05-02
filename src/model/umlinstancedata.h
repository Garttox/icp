#ifndef UMLINSTANCEDATA_H
#define UMLINSTANCEDATA_H

#include "umlclassdata.h"

#include <QString>



class UMLInstanceData
{
public:
    UMLInstanceData(QString name, UMLClassData *className, int posX);
private:
    QString name;
    UMLClassData *className;
    int posX;
};

#endif // UMLINSTANCEDATA_H
