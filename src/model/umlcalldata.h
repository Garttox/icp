#ifndef UMLCALLDATA_H
#define UMLCALLDATA_H

#include "umlcalltype.h"
#include "umlinstancedata.h"
#include "umlmethoddata.h"

#include <QString>



class UMLCallData
{
public:
    UMLCallData(UMLInstanceData *source, UMLInstanceData *destination, UMLMethodData *method, bool async, int duration, int atTime, UMLCallType type);
private:
    UMLInstanceData *source;
    UMLInstanceData *destination;
    UMLMethodData *method;
    bool async;
    int duration; // 0 -> 1000
    int atTime; // 0 -> 1000
    UMLCallType type;
};

#endif // UMLCALLDATA_H
