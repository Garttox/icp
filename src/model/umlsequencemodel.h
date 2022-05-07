#ifndef UMLSEQUENCEMODEL_H
#define UMLSEQUENCEMODEL_H

#include "umlcallmodel.h"
#include "umlinstancemodel.h"

#include <QString>

class UMLSequenceModel : public QObject
{
    Q_OBJECT
public:
    UMLSequenceModel(QString name);
    UMLSequenceModel(QString name, QList<UMLInstanceModel *> instances, QList<UMLCallModel *> calls);
    ~UMLSequenceModel();
    void addInstance(UMLInstanceModel *instance);
    void addCall(UMLCallModel *call);
    UMLInstanceModel* findInstanceByName(QString instanceName);
    QString getName();
    QList<UMLInstanceModel *> getInstances() const;
    QList<UMLCallModel *> getCalls() const;
    UMLCallModel *instanceCreatedBy(UMLInstanceModel *umlInstanceModel);
    UMLCallModel *instanceDestroyedBy(UMLInstanceModel *umlInstanceModel);
signals:
    void instanceModelAdded(UMLInstanceModel *umlInstanceModel);
    void callModelAdded(UMLCallModel *umlCallModel);

private:
    QString name;
    QList<UMLInstanceModel *> instances;
    QList<UMLCallModel *> calls;
};

#endif // UMLSEQUENCEMODEL_H
