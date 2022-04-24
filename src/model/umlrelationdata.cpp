#include "umlrelationdata.h"

UMLRelationData::UMLRelationData(UMLClassData *source, UMLClassData *destination, UMLRelationType *type)
    : source(source), destination(destination), type(type)
{}
