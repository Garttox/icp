#ifndef UMLCALLDATA_H
#define UMLCALLDATA_H

#include "umlinstancedata.h"
#include "umlmethoddata.h"

#include <QString>



class UMLCallData
{
public:
    UMLCallData(UMLInstanceData *source, UMLInstanceData *destination, UMLMethodData *method, bool async, int duration, int atTime);
private:
    UMLInstanceData *source;
    UMLInstanceData *destination;
    UMLMethodData *method;
    bool async;
    int duration;
    int atTime;
};

#endif // UMLCALLDATA_H
