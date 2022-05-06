#ifndef UMLCALLDATA_H
#define UMLCALLDATA_H

#include "data.h"
#include "model/umlcallmodel.h"

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
