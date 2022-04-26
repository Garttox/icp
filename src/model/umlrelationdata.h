#ifndef UMLRELATIONDATA_H
#define UMLRELATIONDATA_H

#include "umlclassdata.h"
#include "umlrelationtype.h"

class UMLRelationData
{
public:
    UMLRelationData(UMLClassData *source, UMLClassData *destination, UMLRelationType *type);
private:
    UMLClassData *source;
    UMLClassData *destination;
    UMLRelationType *type;
};

#endif // UMLRELATIONDATA_H
