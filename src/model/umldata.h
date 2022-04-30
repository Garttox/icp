#ifndef UMLDATA_H
#define UMLDATA_H

#include <QSet>
#include <QObject>

#include "umlclassdata.h"
#include "umlrelationdata.h"

class UMLData : public QObject
{
    Q_OBJECT
public:
    UMLData();
    ~UMLData();
    bool loadData(QJsonObject json);
    void addClass(UMLClassData *classData);
    void removeClass(UMLClassData *classData);

    void addRelation(UMLRelationData *relation);
    void removeRelation(UMLRelationData *umlRelationData);

    void clearData();

    UMLClassData* findClassByName(QString className);
    QSet<UMLClassData *> *getClasses();
    QSet<UMLRelationData *> getRelationsWithSourceClass(UMLClassData *umlClassData);
public slots:
    void classModelChanged(UMLClassData *umlClassData);
    void relationModelChanged(UMLRelationData *umlRelationData);

signals:
    void classModelAdded(UMLClassData *umlClassData);
    void classModelEdited(UMLClassData *umlClassData);
    void relationModelAdded(UMLRelationData *umlRelationData);
    void relationModelEdited(UMLRelationData *umlRelationData);
    void relationModelRemoved(UMLRelationData *umlRelationData);
    void umlModelCleared();

private:
    QSet<UMLClassData *> *classes;
    QSet<UMLRelationData *> *relations;
};

#endif // UMLDATA_H
