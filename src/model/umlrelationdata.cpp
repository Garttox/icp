#include "umlrelationdata.h"

UMLRelationData::UMLRelationData(UMLClassData *src, UMLClassData *dest, UMLRelationType *type, int srcAnchorId, int destAnchorId)
    : source(src), destination(dest), type(type), sourceAnchorId(srcAnchorId), destinationAnchorId(destAnchorId)
{}
