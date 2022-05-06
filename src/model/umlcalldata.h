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
    UMLInstanceData *getDestination() const;
    UMLInstanceData *getSource() const;
    UMLCallType getType() const;
    int getAtTime() const;

    static constexpr int MAX_AT_TIME = 1000;
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
