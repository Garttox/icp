/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umldata.h
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#ifndef UMLDATA_H
#define UMLDATA_H

#include <QSet>
#include <QObject>

#include "umlclassdata.h"
#include "umlrelationdata.h"
#include "umlsequencedata.h"

/**
 * @brief Data class containing the whole data model of application.
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */
class UMLData : public QObject
{
    Q_OBJECT
public:
    UMLData();
    ~UMLData();
    bool loadData(QJsonObject json);
    QJsonObject getSaveData();
    void addClass(UMLClassData *umlClassData);
    void removeClass(UMLClassData *umlClassData);

    void addRelation(UMLRelationData *umlRelationData);
    void removeRelation(UMLRelationData *umlRelationData);

    void addSequence(UMLSequenceData* umlSequenceData);
    void removeSequence(UMLSequenceData* umlSequenceData);

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
    QSet<UMLSequenceData *> *sequences;
};

#endif // UMLDATA_H
