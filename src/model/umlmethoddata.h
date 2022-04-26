#ifndef UMLMETHODDATA_H
#define UMLMETHODDATA_H

#include <QVector>

#include "umlidentifier.h"
class UMLMethodParameterData;

class UMLMethodData : public UMLIdentifier
{
public:
    UMLMethodData(QString name, QString type, UMLAccessType *access);
    ~UMLMethodData();
    void addParameter(UMLMethodParameterData *parameter);
    QString toString();
private:
    QVector<UMLMethodParameterData *> parameters;
};

#endif // UMLMETHODDATA_H
