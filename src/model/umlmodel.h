/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umlmodel.h
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#ifndef UMLMODEL_H
#define UMLMODEL_H

#include <QSet>
#include <QObject>

#include "umlclassmodel.h"
#include "umlrelationmodel.h"
#include "umlsequencemodel.h"

/**
 * @brief Class containing the whole model of application.
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */
class UMLModel : public QObject
{
    Q_OBJECT
public:
    UMLModel();
    ~UMLModel();

    void addClass(UMLClassModel *umlClassModel);
    void removeClass(UMLClassModel *umlClassModel);

    void addRelation(UMLRelationModel *umlRelationModel);
    void removeRelation(UMLRelationModel *umlRelationModel);

    void addSequence(UMLSequenceModel* umlSequenceModel);
    void removeSequence(UMLSequenceModel* umlSequenceModel);

    void clear();

    UMLClassModel* findClassByName(QString className);
    QList<UMLClassModel *> getClasses() const;
    QList<UMLRelationModel *> getRelations() const;
    QList<UMLSequenceModel *> getSequences() const;
    QSet<UMLRelationModel *> getRelationsWithSourceClass(UMLClassModel *umlClassModel);

public slots:
    void classModelChanged(UMLClassModel *umlClassModel);
    void relationModelChanged(UMLRelationModel *umlRelationModel);

signals:
    void classModelAdded(UMLClassModel *umlClassModel);
    void classModelEdited(UMLClassModel *umlClassModel);
    void classModelRemoved(UMLClassModel *umlClassModel);
    void relationModelAdded(UMLRelationModel *umlRelationModel);
    void relationModelEdited(UMLRelationModel *umlRelationModel);
    void relationModelRemoved(UMLRelationModel *umlRelationModel);
    void sequenceModelAdded(UMLSequenceModel *umlSequenceModel);
    void umlModelCleared();

private:
    QSet<UMLClassModel *> classes;
    QSet<UMLRelationModel *> relations;
    QSet<UMLSequenceModel *> sequences;

};

#endif // UMLMODEL_H
