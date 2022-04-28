#include <QGraphicsScene>
#include "umlrelation.h"
#include "umlclass.h"
#include "umlclassnotifier.h"


UMLRelation::UMLRelation(UMLClass* sourceClass, UMLRelationAnchor* sourceAnchor, UMLRelationAnchor* destinationAnchor) :
    QObject(), QGraphicsLineItem(),
    sourceClass(sourceClass), sourceAnchor(sourceAnchor), destinationAnchor(destinationAnchor)
{
    setColorPen();
    setCorrectPosition();
    setFlag(ItemIsSelectable);
    connect(UMLClassNotifier::getInstance(), SIGNAL(anchorRemoved(UMLRelationAnchor*)),
            this, SLOT(onAnchorRemoved(UMLRelationAnchor*)));
}

void UMLRelation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setCorrectPosition();
    QGraphicsLineItem::paint(painter, option, widget);
}

void UMLRelation::remove()
{
    scene()->removeItem(this);
    delete this;
}

void UMLRelation::onAnchorRemoved(UMLRelationAnchor *anchor)
{
    if (anchor == sourceAnchor || anchor == destinationAnchor)
    {
        remove();
    }
}

void UMLRelation::setColorPen()
{
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(120, 135, 140));
    setPen(pen);
}


void UMLRelation::setCorrectPosition()
{
    QPointF sourcePoint = sourceAnchor->sceneBoundingRect().center();
    QPointF destinationPoint = destinationAnchor->sceneBoundingRect().center();
    setLine(sourcePoint.x(), sourcePoint.y(), destinationPoint.x(), destinationPoint.y());
}


