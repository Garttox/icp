#ifndef UMLIDENTIFIER_H
#define UMLIDENTIFIER_H

#include <QString>

class UMLAccessType;

class UMLIdentifier
{
public:
    UMLIdentifier(QString name, QString type, UMLAccessType *access);
    ~UMLIdentifier();
protected:
    QString name;
    QString type;
    UMLAccessType *access;
};

#endif // UMLIDENTIFIER_H
