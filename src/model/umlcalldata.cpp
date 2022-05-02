#include "umlcalldata.h"

UMLCallData::UMLCallData(UMLInstanceData *source, UMLInstanceData *destination, UMLMethodData *method, bool async, int duration, int atTime) :
    source(source), destination(destination), method(method), async(async), duration(duration), atTime(atTime)
{}
