#ifndef UMLRELATIONDATA_H
#define UMLRELATIONDATA_H

#include "data.h"
#include "model/umlrelationmodel.h"

class UMLRelationData : Data<UMLRelationModel>
{
public:
    virtual ~UMLRelationData() {};
    bool load(QJsonObject object) override;
    void fromModel(UMLRelationModel *model) override;
    UMLRelationModel *toModel() override;

    QString getSource() const;
    QString getDestination() const;
    QString getType() const;
    int getSourceAnchorId() const;
    int getDestinationAnchorId() const;

private:
    QString source;
    QString destination;
    QString type;
    int sourceAnchorId;
    int destinationAnchorId;

};

#endif // UMLRELATIONDATA_H
