#ifndef UMLRELATIONTYPE_H
#define UMLRELATIONTYPE_H

#include <QString>
#include <QStringList>

class UMLRelationType
{
public:
    enum RelationType {
        ASSOCIATION,
        AGREGATION,
        COMPOSITION,
        GENERALISATION
    };
    UMLRelationType(RelationType type);
    UMLRelationType(QString strType);

    bool operator==(const RelationType rhs);
    bool operator==(const UMLRelationType& rhs);

    QString toString() const;
    static QStringList asStringList();
private:
    RelationType type;
};

#endif // UMLRELATIONTYPE_H
