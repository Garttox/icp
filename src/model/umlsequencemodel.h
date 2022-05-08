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
    UMLSequenceModel(QString name, QSet<UMLInstanceModel *> instances, QSet<UMLCallModel *> calls);
    ~UMLSequenceModel();
    void addInstance(UMLInstanceModel *instance);
    void removeInstance(UMLInstanceModel *instance);
    void addCall(UMLCallModel *call);
    void removeCall(UMLCallModel *call);
    UMLInstanceModel* findInstanceByName(QString instanceName);
    QString getName();
    QList<UMLInstanceModel *> getInstances() const;
    QList<UMLCallModel *> getCalls() const;
    UMLCallModel *instanceCreatedBy(UMLInstanceModel *umlInstanceModel);
    UMLCallModel *instanceDestroyedBy(UMLInstanceModel *umlInstanceModel);

private slots:
    void instanceModelChanged(UMLInstanceModel *umlInstanceModel);
    void callModelChanged(UMLCallModel *umlCallModel);

signals:
    void instanceModelAdded(UMLInstanceModel *umlInstanceModel);
    void instanceModelEdited(UMLInstanceModel *umlInstanceModel);
    void instanceModelRemoved(UMLInstanceModel *umlInstanceModel);
    void callModelAdded(UMLCallModel *umlCallModel);
    void callModelEdited(UMLCallModel *umlCallModel);
    void callModelRemoved(UMLCallModel *umlCallModel);

private:
    QString name;
    QSet<UMLInstanceModel *> instances;
    QSet<UMLCallModel *> calls;
};

#endif // UMLSEQUENCEMODEL_H
