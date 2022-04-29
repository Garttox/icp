#ifndef UMLCLASSNOTIFIER_H
#define UMLCLASSNOTIFIER_H

#include <QObject>
#include "umlrelationanchor.h"

class UMLClassNotifier : public QObject
{
    Q_OBJECT
public:
    UMLClassNotifier(UMLClassNotifier const&) = delete;
    void operator=(UMLClassNotifier const&) = delete;
    static UMLClassNotifier* getInstance();

private:
    explicit UMLClassNotifier(QObject *parent = nullptr);

signals:
    void anchorDragged(UMLRelationAnchor *anchor, QPointF endpoint);
    void anchorDragReleased(UMLRelationAnchor *source, UMLRelationAnchor* destination);
    void anchorRemoved(UMLRelationAnchor *anchor);
    void classRemoved(UMLClass *umlClass);

};

#endif // UMLCLASSNOTIFIER_H
