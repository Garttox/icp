#ifndef UMLRELATIONMODEL_H
#define UMLRELATIONMODEL_H

#include <QJsonObject>
#include "umlclassmodel.h"
#include "umlrelationtype.h"

class UMLRelationModel : public QObject
{
    Q_OBJECT
public:
    UMLRelationModel(UMLClassModel *src, UMLClassModel *dest, UMLRelationType type, int srcAnchorId, int destAnchorId);
    UMLClassModel *getSource() const;
    UMLClassModel *getDestination() const;
    UMLRelationType getType() const;
    int getSourceAnchorId() const;
    int getDestinationAnchorId() const;
    void setType(UMLRelationType type);
    QJsonObject getSaveData();

signals:
    void modelChanged(UMLRelationModel *umlRelationModel);

private:
    UMLClassModel *source;
    UMLClassModel *destination;
    UMLRelationType type;

    const int sourceAnchorId;
    const int destinationAnchorId;
};

#endif // UMLRELATIONMODEL_H