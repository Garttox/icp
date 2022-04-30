#ifndef UMLRELATIONDATA_H
#define UMLRELATIONDATA_H

#include <QJsonObject>
#include "umlclassdata.h"
#include "umlrelationtype.h"

class UMLRelationData : public QObject
{
    Q_OBJECT
public:
    UMLRelationData(UMLClassData *src, UMLClassData *dest, UMLRelationType type, int srcAnchorId, int destAnchorId);
    UMLClassData *getSource() const;
    UMLClassData *getDestination() const;
    UMLRelationType getType() const;
    int getSourceAnchorId() const;
    int getDestinationAnchorId() const;
    void setType(UMLRelationType type);
    QJsonObject getSaveData();

signals:
    void modelChanged(UMLRelationData *umlRelationData);

private:
    UMLClassData *source;
    UMLClassData *destination;
    UMLRelationType type;

    const int sourceAnchorId;
    const int destinationAnchorId;
};

#endif // UMLRELATIONDATA_H
