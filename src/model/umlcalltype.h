#ifndef UMLCALLTYPE_H
#define UMLCALLTYPE_H

#include <QString>

class UMLCallType
{
public:
    enum CallType {
        MESSAGE,
        CREATE,
        DESTROY
    };

    UMLCallType(CallType type);
    UMLCallType(QString type);

    bool operator==(const CallType rhs);
    bool operator==(const UMLCallType& rhs);
    QString toString() const;
private:
    CallType type;
};

#endif // UMLCALLTYPE_H
