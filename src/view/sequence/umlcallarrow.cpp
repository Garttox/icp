#include "umlcall.h"
#include "umlcallarrow.h"
#include "umlinstance.h"

#include <QPainter>
#include <algorithm>

UMLCallArrow::UMLCallArrow(UMLCall *parent)
    : QObject(), QGraphicsLineItem(parent)
{
    setCorrectPosition();
}

QRectF UMLCallArrow::boundingRect() const
{
    QPointF p1 = line().p1();
    QPointF p2 = line().p2();
    QFontMetricsF fontMetrics(TEXT_FONT);
    qreal offset = std::max(ARROW_SIZE / 2, fontMetrics.height());
    qreal xSize;
    qreal fontWidth = fontMetrics.width(getMethodDisplayName());
    if (p2.x() - p1.x() < 0)
    {
        xSize = std::min(p2.x() - p1.x(), -fontWidth);
    }
    else
    {
        xSize = std::max(p2.x() - p1.x(), fontWidth);
    }
    QSizeF size(xSize, p2.y() - p1.y());

    return QRectF(p1, size)
        .normalized()
        .adjusted(-offset, -offset, offset, offset);
}

QPainterPath UMLCallArrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

// - - - - - protected - - - - -

void UMLCallArrow::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void UMLCallArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setCorrectPosition();

    // draw line
    QGraphicsLineItem::paint(painter, option, widget);

    // draw arrow head
    setArrowHead();
    drawArrowHead(painter);

    painter->drawText(boundingRect(), Qt::AlignTop | Qt::AlignHCenter, getMethodDisplayName());
}

// - - - - - private - - - - -

void UMLCallArrow::setCorrectPosition()
{
    UMLCall *parent = static_cast<UMLCall*>(parentItem());
    qreal top = parent->boundingRect().top();
    qreal distance = parent->getSourceDistance();
    if (distance < 0)
    {
        setLine(-parent->boundingRect().width()/2, top, distance, top);
    }
    else
    {
        setLine(parent->boundingRect().width()/2, top, distance, top);
    }
}

void UMLCallArrow::setArrowHead()
{
    arrowHead.clear();

    qreal angle = line().angle();
    qreal x = line().p1().x();
    qreal y = line().p1().y();

    arrowHead.append(QPoint(x + ARROW_SIZE, y - (ARROW_SIZE  / 2)));
    arrowHead.append(QPoint(x, y));
    arrowHead.append(QPoint(x + ARROW_SIZE, y + (ARROW_SIZE  / 2)));

    arrowHead = QTransform()
        .translate(x, y)
        .rotate(-angle)
        .translate(-x, -y)
        .map(arrowHead);
}

void UMLCallArrow::drawArrowHead(QPainter *painter)
{
    QPainterPath path;
    path.addPolygon(arrowHead);
    painter->fillPath(path, QColor(50, 50, 50));
    painter->drawPolygon(arrowHead);
}

QString UMLCallArrow::getMethodDisplayName() const
{
    UMLCallModel *umlCallModel = static_cast<UMLCall*>(parentItem())->getUMLCallModel();
    return umlCallModel->getDisplayMethodName();
}
