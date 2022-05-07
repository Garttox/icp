/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlrelationdata.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLRELATIONDATA_H
#define UMLRELATIONDATA_H

#include "data.h"
#include "model/umlrelationmodel.h"

/**
 * @brief Data class for storing relation data.
 */
class UMLRelationData : Data<UMLRelationModel>
{
public:
    virtual ~UMLRelationData() {};
    bool load(QJsonObject object) override;
    void fromModel(UMLRelationModel *model) override;
    QJsonObject toJson() const;
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
