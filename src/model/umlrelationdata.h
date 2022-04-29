#ifndef UMLRELATIONDATA_H
#define UMLRELATIONDATA_H

#include "umlclassdata.h"
#include "umlrelationtype.h"

class UMLRelationData
{
public:
    UMLRelationData(UMLClassData *src, UMLClassData *dest, UMLRelationType type, int srcAnchorId, int destAnchorId);
    UMLClassData *getSource() const;
    UMLClassData *getDestination() const;
    UMLRelationType getType() const;
    int getSourceAnchorId() const;
    int getDestinationAnchorId() const;

private:
    UMLClassData *source;
    UMLClassData *destination;
    UMLRelationType type;

    const int sourceAnchorId;
    const int destinationAnchorId;
};

#endif // UMLRELATIONDATA_H
