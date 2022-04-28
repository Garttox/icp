#include "umlrelationanchor.h"
#include "umlclassnotifier.h"
#include "umlclass.h"
#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

UMLRelationAnchor::UMLRelationAnchor(qreal relX, qreal relY, UMLClass* parent):
    QObject(),
    QGraphicsEllipseItem(parent),
    relX(relX), relY(relY)
{
    setColorPen();

    setPositionRelativeToParent();
    setVisible(false);

    setDragLineProperties();
}

void UMLRelationAnchor::setPositionRelativeToParent()
{
    setRect(getRelativeRect());
}

void UMLRelationAnchor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        dragLine.setLine(0, 0, 0, 0);
        dragLine.setVisible(true);
        update();
    }
}

void UMLRelationAnchor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        // hide drag line first, so we can get item below
        dragLine.setVisible(false);

        // notify about anchor drag released
        QGraphicsItem *droppedAt = scene()->itemAt(event->scenePos(), QTransform());
        UMLRelationAnchor* anchor = dynamic_cast<UMLRelationAnchor*>(droppedAt);

        // anchor is nullptr if dynamic cast fails
        emit UMLClassNotifier::getInstance()->anchorDragReleased(this, anchor);

        update();
    }
}

void UMLRelationAnchor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF start = getRelativeRect().center();
    QPointF end = event->pos();
    dragLine.setLine(start.x(), start.y(), end.x(), end.y());
    update();
    emit UMLClassNotifier::getInstance()->anchorDragged(this, event->scenePos());
}

QRectF UMLRelationAnchor::getRelativeRect() const
{
    QRectF bounds = static_cast<UMLClass*>(parentItem())->boundingRect();
    qreal x = relX * 0.5 * bounds.width();
    qreal y = relY * 0.5 * bounds.height();
    return QRectF(x - (SIZE / 2), y - (SIZE / 2), SIZE, SIZE);
}

void UMLRelationAnchor::setColorPen()
{
    QPen pen(OUTLINE_COLOR);
    setBrush(BRUSH_COLOR);
    pen.setWidth(2);
    setPen(pen);
}

void UMLRelationAnchor::setDragLineProperties()
{
    dragLinePen.setColor(DRAGLINE_COLOR);
    dragLinePen.setWidth(2);
    dragLine.setPen(dragLinePen);
    dragLine.setParentItem(this);
}

