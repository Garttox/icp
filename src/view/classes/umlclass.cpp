#include <QtGui>
#include <QStyleOptionGraphicsItem>

#include "umlclass.h"

UMLClass::UMLClass(UMLClassData *umlClassData) : umlClassData(umlClassData)
{
    myTextColor = Qt::darkGreen;
    myOutlineColor = Qt::darkBlue;
    myBackgroundColor = Qt::white;

    setFlags(ItemIsMovable | ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
}

void UMLClass::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget * /* widget */)
{
    QPen pen;
    if (option->state & QStyle::State_Selected) {
        //pen.setStyle(Qt::DotLine);
        pen = QPen(QColor("red"));
        pen.setWidth(2);
    } else {
        pen = QPen(myOutlineColor);
    }
    painter->setPen(pen);
    painter->setBrush(myBackgroundColor);
    QRectF rect = outlineRect();
    painter->drawRect(rect);
    painter->setPen(myTextColor);

    //painter->drawText(rect, Qt::AlignCenter, a);
    QFontMetricsF metrics{qApp->font()};
    //painter->drawText(rect, Qt::AlignCenter, umlClassData->getName());
    QSet<UMLFieldData *> *fields = umlClassData->getFields();
    QSet<UMLMethodData *> *methods = umlClassData->getMethods();
    QPointF point = rect.topLeft();
    qreal offsetX = 3.0;
    point.setY(point.y() + metrics.height());
    point.setX(point.x() + offsetX);

    // class name
    painter->drawText(point, umlClassData->getName());
    point.setY(point.y() + metrics.height()/2);
    point.setX(point.x() - offsetX);
    painter->drawLine(point, QPointF(point.x() + rect.width(), point.y()));
    point.setX(point.x() + offsetX);
    point.setY(point.y() + metrics.height());

    // methods
    foreach(auto *method, *methods){
        painter->drawText(point, method->toString());
        point.setY(point.y() + metrics.height());
    }
    // separator
    point.setX(point.x() - offsetX);
    point.setY(point.y() - metrics.height()/2);
    painter->drawLine(point, QPointF(point.x() + rect.width(), point.y()));
    point.setX(point.x() + offsetX);
    point.setY(point.y() + metrics.height());
    // fields
    foreach(auto *field, *fields){
        painter->drawText(point, field->toString());
        point.setY(point.y() + metrics.height());
    }
}

QRectF UMLClass::boundingRect() const
{
    return outlineRect();
}

void UMLClass::modelChanged()
{

}

qreal UMLClass::maxTextWidth() const
{
    QFontMetricsF metrics{qApp->font()};
    QSet<UMLFieldData *> *fields = umlClassData->getFields();
    QSet<UMLMethodData *> *methods = umlClassData->getMethods();
    qreal maxWidth = metrics.width(umlClassData->getName());

    foreach(auto *method, *methods){
        qreal rowWidth = metrics.width(method->toString());
        if (rowWidth >  maxWidth)
            maxWidth = rowWidth;
    }

    foreach(auto *field, *fields){
        qreal rowWidth = metrics.width(field->toString());
        if (rowWidth >  maxWidth)
            maxWidth = rowWidth;
    }
    return maxWidth;
}

QRectF UMLClass::outlineRect() const
{
    const int Padding = 8;
    QFontMetricsF metrics{qApp->font()};
    QSet<UMLFieldData *> *fields = umlClassData->getFields();
    QSet<UMLMethodData *> *methods = umlClassData->getMethods();
    QRectF rect = QRectF(0, 0, maxTextWidth(), (metrics.height())*(fields->size() + methods->size() + 1) + 10);
    rect.adjust(-Padding, -Padding, +Padding, +Padding);
    rect.translate(-rect.center());
    return rect;
}
