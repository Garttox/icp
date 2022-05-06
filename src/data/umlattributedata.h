#ifndef UMLATTRIBUTEDATA_H
#define UMLATTRIBUTEDATA_H
#include <QString>


class UMLAttributeData
{
public:
    QString getName() const;
    QString getType() const;
    QString getAccess() const;

protected:
    QString name;
    QString type;
    QString access;


};

#endif // UMLATTRIBUTEDATA_H
