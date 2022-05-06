#include "umlinstance.h"

#include <QColor>
#include <QFontMetricsF>
#include <QPainter>
#include <QPen>

UMLInstance::UMLInstance(UMLInstanceModel *umlInstanceModel)
    : umlInstanceModel(umlInstanceModel)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setPos(umlInstanceModel->getPosX(), 100);
}

QRectF UMLInstance::boundingRect() const
{
    return outlineRect();
}

// - - - - - protected - - - - -

void UMLInstance::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */* widget */)
{
    QPen pen = QPen(isSelected() ? SELECTED_OUTLINE_COLOR : OUTLINE_COLOR);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(BACKGROUND_COLOR);
    QRectF rect = outlineRect();
    painter->drawRect(rect);
    painter->setPen(TEXT_COLOR);

    painter->drawText(rect, umlInstanceModel->getDisplayName());
}

QVariant UMLInstance::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            setZValue(isSelected() ? 1 : 0);
            break;
        case QGraphicsItem::ItemPositionHasChanged:
            umlInstanceModel->setPosX(this->pos().x());
            setPos(this->pos().x(), DEFAULT_POSY);
            break;
        default:
            break;  // Keeps Qt Creator without warnings
    }
    return QGraphicsItem::itemChange(change, value);
}

// - - - - - private - - - - -

QRectF UMLInstance::outlineRect() const
{

    QFontMetricsF fontMetrics(NAME_FONT);
    QRectF rect = fontMetrics.boundingRect(umlInstanceModel->getDisplayName());
    rect.adjust(-PADDING, -PADDING, +PADDING, +PADDING);
    rect.translate(-rect.center());
    return rect;
}
