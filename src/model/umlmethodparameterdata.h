#ifndef UMLMETHODPARAMETERDATA_H
#define UMLMETHODPARAMETERDATA_H

#include <QString>

class UMLMethodParameterData
{
public:
    UMLMethodParameterData(QString name, QString type);
    QString toString();
private:
    QString name;
    QString type;
};

#endif // UMLMETHODPARAMETERDATA_H
