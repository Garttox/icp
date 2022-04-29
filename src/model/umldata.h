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
    void removeRelation(UMLRelationData *relation);

    void clearData();

    UMLClassData* findClassByName(QString clsName);
    QSet<UMLClassData *> *getClasses();
public slots:
    void classModelChanged();
    void relationModelChanged();

signals:
    void classModelAdded(UMLClassData *classData);
    void relationModelAdded(UMLRelationData *relationData);
    void relationModelRemoved(UMLRelationData *relationData);
    void umlModelCleared();

private:
    QSet<UMLClassData *> *classes;
    QSet<UMLRelationData *> *relations;
};

#endif // UMLDATA_H
