#include <QtGui>
#include <QStyleOptionGraphicsItem>

#include "umlclass.h"

UMLClass::UMLClass()
{
    myTextColor = Qt::darkGreen;
    myOutlineColor = Qt::darkBlue;
    myBackgroundColor = Qt::white;

    setFlags(ItemIsMovable | ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    myText = "gadfgadfgdsfgdsfg\n"
             "sdfgsdfgsdfgdsfgsdfg\n"
             "sdfg\n"
             "sdfg\n"
             "sdfg\n"
             "sdfg\n"
             "sd\n"
             "fg\n"
             "sdfg\n"
             "gdfgsdfg";
}

void UMLClass::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget * /* widget */)
{
    QPen pen(myOutlineColor);
    if (option->state & QStyle::State_Selected) {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }
    painter->setPen(pen);
    painter->setBrush(myBackgroundColor);
    QRectF rect = outlineRect();
    painter->drawRect(rect);

    painter->setPen(myTextColor);
    painter->drawText(rect, Qt::AlignCenter, myText);
}

QRectF UMLClass::boundingRect() const
{
    return outlineRect();
}

QRectF UMLClass::outlineRect() const
{
    const int Padding = 8;
    QFontMetricsF metrics{qApp->font()};
    QRectF rect = QRectF(0, 0, metrics.width(myText) ,metrics.height()*10);
    rect.adjust(-Padding, -Padding, +Padding, +Padding);
    rect.translate(-rect.center());
    return rect;
}
