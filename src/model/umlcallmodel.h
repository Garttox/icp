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
    UMLInstanceModel *getDestination() const;
    UMLInstanceModel *getSource() const;
    UMLCallType getType() const;
    int getAtTime() const;
    int getDuration() const;
    QString getDisplayMethodName() const;

    static constexpr qreal RELATIVE_MAX_LIFE = 1000;
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
