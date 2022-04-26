#ifndef UMLIDENTIFIER_H
#define UMLIDENTIFIER_H

#include <QString>

class UMLAccessType;

class UMLIdentifier
{
public:
    UMLIdentifier(QString name, QString type, UMLAccessType *access);
    ~UMLIdentifier();
    QString getName() const;
    QString getType() const;
    UMLAccessType *getAccess() const;
    void setName(QString name);
    void setType(QString type);
    void setAccess(UMLAccessType *access);
protected:
    QString name;
    QString type;
    UMLAccessType *access;
};

#endif // UMLIDENTIFIER_H
