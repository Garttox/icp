#include "umlinstance.h"

#include <QColor>
#include <QFontMetricsF>
#include <QPainter>
#include <QPen>

UMLInstance::UMLInstance(UMLInstanceData *umlInstanceData)
    : umlInstanceData(umlInstanceData)
{

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

    painter->drawText(rect, umlInstanceData->getDisplayName());
}

// - - - - - private - - - - -

QRectF UMLInstance::outlineRect() const
{

    QFontMetricsF fontMetrics(NAME_FONT);
    QRectF rect = fontMetrics.boundingRect(umlInstanceData->getDisplayName());
    rect.adjust(-PADDING, -PADDING, +PADDING, +PADDING);
    rect.translate(-rect.center());
    return rect;
}
