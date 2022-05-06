#include "umlcall.h"
#include "umlinstance.h"

#include <QPainter>
#include <QPen>
#include <QRectF>

UMLCall::UMLCall(UMLCallModel *umlCallModel, UMLInstance *sourceInstance, UMLInstance *destinationInstance)
    : QObject(), QGraphicsItem(), umlCallModel(umlCallModel),
      sourceInstance(sourceInstance), destinationInstance(destinationInstance)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setCorrectPosition();
}

QRectF UMLCall::boundingRect() const
{
    return outlineRect();
}

// - - - - - protected - - - - -

void UMLCall::paint(QPainter *painter, const QStyleOptionGraphicsItem */* option */, QWidget */* widget */)
{
    setCorrectPosition();

    QPen pen = QPen(isSelected() ? SELECTED_OUTLINE_COLOR : OUTLINE_COLOR);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(BACKGROUND_COLOR);
    QRectF rect = outlineRect();
    painter->drawRect(rect);
}

QVariant UMLCall::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            setZValue(isSelected() ? 1 : 0);
            break;
        case QGraphicsItem::ItemPositionHasChanged:
            setCorrectPosition();
            break;
        default:
            break;  // Keeps Qt Creator without warnings
    }
    return QGraphicsItem::itemChange(change, value);
}

// - - - - - private - - - - -

QRectF UMLCall::outlineRect() const
{
    QRectF rect = QRectF(0,0,15,40);
    rect.translate(-rect.center());
    return rect;
}

void UMLCall::setCorrectPosition()
{
    qreal destinationPosX = destinationInstance->getPosX();
    if (this->pos().y() < destinationInstance->getStartCenter().y())
    {
        setPos(destinationPosX, destinationInstance->getStartCenter().y());
    }
    else if (this->pos().y() > destinationInstance->getEndCenter().y())
    {
        setPos(destinationPosX, destinationInstance->getEndCenter().y());
    }
    else
    {
        setPos(destinationPosX, this->pos().y());
    }
}
