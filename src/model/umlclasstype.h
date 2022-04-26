#ifndef UMLCLASSTYPE_H
#define UMLCLASSTYPE_H

#include <QString>

class UMLClassType
{
public:
    enum ClassType
    {
        CLASS,
        INTERFACE
    };

    UMLClassType(ClassType classType);
    UMLClassType(QString strClassType);
    bool operator==(const ClassType rhs) const;
    bool operator==(const UMLClassType& rhs) const;
private:
    ClassType type;
};


#endif // UMLCLASSTYPE_H
