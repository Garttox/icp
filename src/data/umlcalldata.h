/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlcalldata.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLCALLDATA_H
#define UMLCALLDATA_H

#include "data.h"
#include "model/umlcallmodel.h"

/**
 * @brief Data class for holding UML call/message data.
 */
class UMLCallData : Data<UMLCallModel>
{

public:
    virtual ~UMLCallData() {};
    bool load(QJsonObject object) override;
    void fromModel(UMLCallModel *model) override;
    UMLCallModel *toModel() override;

    QString getType() const;
    QString getSource() const;
    QString getDestination() const;
    QString getMethod() const;
    bool getAsync() const;
    int getDuration() const;
    int getAtTime() const;

private:
    QString type;
    QString source;
    QString destination;
    QString method;
    bool async;
    int duration;
    int atTime;

};

#endif // UMLCALLDATA_H
