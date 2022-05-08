#include "newcalldialog.h"
#include "umlinstance.h"
#include "umlinstancelifeline.h"

#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

UMLInstanceLifeLine::UMLInstanceLifeLine(UMLInstance *parent)
    : QObject(), QGraphicsLineItem(parent)
{
    setPenStyle();
}

QRectF UMLInstanceLifeLine::boundingRect() const
{
    QPointF p1 = line().p1();
    QPointF p2 = line().p2();
    qreal offset = 10;
    QSizeF size(p2.x() - p1.x(), p2.y() - p1.y());

    return QRectF(p1, size)
        .normalized()
        .adjusted(-offset, -offset, offset, offset);
}

QPainterPath UMLInstanceLifeLine::shape() const
{
    QPainterPathStroker pathStroker;
    QPainterPath path;

    pathStroker.setWidth(DETECTION_RADIUS * 2);
    path.moveTo(line().p1());
    path.lineTo(line().p2());
    return pathStroker.createStroke(path);
}

// - - - - - protected - - - - -

void UMLInstanceLifeLine::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    UMLInstance *parent = static_cast<UMLInstance*>(parentItem());
    UMLSequenceModel *umlSequenceModel = parent->getUMLSequenceModel();
    UMLInstanceModel *destination = parent->getUMLInstanceModel();
    int timeAt = (event->pos().y() - line().p1().y()) * (parent->getLifeLength() / UMLCallModel::RELATIVE_MAX_LIFE);
    NewCallDialog *newCallDialog = new NewCallDialog(umlSequenceModel, destination, timeAt);
    newCallDialog->exec();
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
