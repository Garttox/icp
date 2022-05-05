/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umlclassnotifier.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLCLASSNOTIFIER_H
#define UMLCLASSNOTIFIER_H

#include <QObject>
#include "umlrelationanchor.h"
#include "umlrelation.h"

/**
 * @brief Singleton, which serves as intermediary for sending signals between UMLClass, UMLRelation and UMLRelationAnchor.
 * @author Martin Bednář (xbedna77)
 */
class UMLClassNotifier : public QObject
{
    Q_OBJECT
public:
    UMLClassNotifier(UMLClassNotifier const&) = delete;
    void operator=(UMLClassNotifier const&) = delete;
    static UMLClassNotifier* getInstance();

private:
    explicit UMLClassNotifier();

signals:
    void anchorDragged(UMLRelationAnchor *anchor, QPointF endpoint);
    void anchorDragReleased(UMLRelationAnchor *source, UMLRelationAnchor* destination);
    void classRemoved(UMLClass *umlClass);
    void relationRemoved(UMLRelation *umlRelation);

};

#endif // UMLCLASSNOTIFIER_H
