#include "umlcall.h"
#include "umlcallarrow.h"
#include "umlinstance.h"

#include <QPainter>
#include <algorithm>

UMLCallArrow::UMLCallArrow(UMLCall *parent, UMLCallArrowType arrowType)
    : QObject(), QGraphicsLineItem(parent), arrowType(arrowType)
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

    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    setPen(pen);

    // draw arrow head
    setArrowHead();
    drawArrowHead(painter);

    if (arrowType == UMLCallArrowType::RETURN_MESSAGE)
    {
        pen.setStyle(Qt::DashLine);
    }
    else
    {   // draw text
        painter->drawText(boundingRect(), Qt::AlignTop | Qt::AlignHCenter, getMethodDisplayName());
    }
    setPen(pen);


    // draw line
    QGraphicsLineItem::paint(painter, option, widget);
}

// - - - - - private - - - - -

void UMLCallArrow::setCorrectPosition()
{
    UMLCall *parent = static_cast<UMLCall*>(parentItem());
    qreal height;
    if (arrowType == UMLCallArrowType::CALL_MESSAGE)
    {
        height = parent->boundingRect().top();
    }
    else
    {
        height = parent->boundingRect().bottom();
    }

    qreal distance = parent->getSourceDistance();
    if (distance < 0)
    {
        setLine(-parent->boundingRect().width()/2, height, distance, height);
    }
    else
    {
        setLine(parent->boundingRect().width()/2, height, distance, height);
    }
}

void UMLCallArrow::setArrowHead()
{
    arrowHead.clear();

    QPointF arrowHeadLocation;
    qreal angle = line().angle();
    qreal x;
    qreal y;

    if (arrowType == UMLCallArrowType::CALL_MESSAGE)
    {
        arrowHeadLocation = line().p1();
        x = arrowHeadLocation.x();
        y = arrowHeadLocation.y();

        arrowHead.append(QPoint(x + ARROW_SIZE, y - (ARROW_SIZE  / 2)));
        arrowHead.append(QPoint(x, y));
        arrowHead.append(QPoint(x + ARROW_SIZE, y + (ARROW_SIZE  / 2)));
    }
    else
    {
        arrowHeadLocation = line().p2();
        x = arrowHeadLocation.x();
        y = arrowHeadLocation.y();

        arrowHead.append(QPoint(x - ARROW_SIZE, y - (ARROW_SIZE  / 2)));
        arrowHead.append(QPoint(x, y));
        arrowHead.append(QPoint(x - ARROW_SIZE, y + (ARROW_SIZE  / 2)));
    }


    arrowHead = QTransform()
        .translate(x, y)
        .rotate(-angle)
        .translate(-x, -y)
        .map(arrowHead);
}

void UMLCallArrow::drawArrowHead(QPainter *painter)
{
    QPainterPath path;
    QColor color = QColor(255, 255, 255);

    path.addPolygon(arrowHead);
    if (arrowType == UMLCallArrowType::CALL_MESSAGE)
    {
        color = QColor(50, 50, 50);
    }

    painter->fillPath(path, color);
    painter->drawPolygon(arrowHead);
}

QString UMLCallArrow::getMethodDisplayName() const
{
    UMLCallModel *umlCallModel = static_cast<UMLCall*>(parentItem())->getUMLCallModel();
    return umlCallModel->getDisplayMethodName();
}
