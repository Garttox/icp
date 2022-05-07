#ifndef UMLCALLMODEL_H
#define UMLCALLMODEL_H

#include "umlcalltype.h"
#include "umlinstancemodel.h"
#include "umlmethodmodel.h"

#include <QString>



class UMLCallModel
{
public:
    UMLCallModel(UMLInstanceModel *source, UMLInstanceModel *destination, UMLMethodModel *method, bool async, int duration, int atTime, UMLCallType type);
    UMLInstanceModel *getSource() const;
    UMLInstanceModel *getDestination() const;
    UMLMethodModel *getMethod() const;
    bool getAsync() const;
    int getDuration() const;
    int getAtTime() const;
    UMLCallType getType() const;

private:
    UMLInstanceModel *source;
    UMLInstanceModel *destination;
    UMLMethodModel *method;
    bool async;
    int duration; // 0 -> 1000
    int atTime; // 0 -> 1000
    UMLCallType type;
};

#endif // UMLCALLMODEL_H
