#include "umlinstance.h"
#include "umlinstancelifeline.h"

#include <QPen>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

UMLInstanceLifeLine::UMLInstanceLifeLine(UMLInstance *parent)
    : QObject(), QGraphicsLineItem(parent)
{
    setPenStyle();
}

// - - - - - protected - - - - -

void UMLInstanceLifeLine::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void UMLInstanceLifeLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setCorrectPosition();

    // draw line
    QGraphicsLineItem::paint(painter, option, widget);
}

// - - - - - private - - - - -

void UMLInstanceLifeLine::setCorrectPosition()
{
    QRectF parentRect = static_cast<UMLInstance*>(parentItem())->boundingRect();
    QPointF top = parentRect.center();
    top.setY(parentRect.bottom());
    setLine(top.x(), top.y(), top.x(), top.y() + MAX_LENGTH);
}

void UMLInstanceLifeLine::setPenStyle()
{
    QPen pen(LINE_COLOR);
    pen.setStyle(Qt::DashLine);
    setPen(pen);
}
