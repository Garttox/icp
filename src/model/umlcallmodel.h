/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlcallmodel.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef UMLCALLMODEL_H
#define UMLCALLMODEL_H

#include "umlcalltype.h"
#include "umlinstancemodel.h"
#include "umlmethodmodel.h"

#include <QString>

class UMLCallModel : public QObject
{
    Q_OBJECT
public:
    UMLCallModel(UMLInstanceModel *source, UMLInstanceModel *destination, UMLMethodModel *method, bool async, int duration, int atTime, UMLCallType type);
    UMLInstanceModel *getDestination() const;
    UMLInstanceModel *getSource() const;
    UMLCallType getType() const;
    UMLMethodModel *getMethod() const;
    void setMethod(UMLMethodModel *method);
    int getAtTime() const;
    void setAtTime(int atTime);
    int getDuration() const;
    void setDuration(int duration);
    bool getAsync() const;
    void setAsync(bool async);
    QString getDisplayMethodName() const;

    static constexpr qreal RELATIVE_MAX_LIFE = 1000;
signals:
    void modelChanged(UMLCallModel *umlCallModel);
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
