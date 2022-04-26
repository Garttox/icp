#include <QtGui>
#include <QStyleOptionGraphicsItem>
#include <algorithm>

#include "umlclass.h"

UMLClass::UMLClass(UMLClassData *umlClassData) : umlClassData(umlClassData)
{
    myTextColor = Qt::darkGreen;
    myOutlineColor = Qt::darkBlue;
    myBackgroundColor = Qt::white;

    setFlags(ItemIsMovable | ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);

    setPos(umlClassData->getPosX(), umlClassData->getPosY());
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
    qreal maxWidth = std::max(metrics.width(umlClassData->getName()), MIN_WIDTH);

    foreach(auto *method, *methods){
        qreal rowWidth = metrics.width(method->toString());
        maxWidth = std::max(rowWidth, maxWidth);
    }

    foreach(auto *field, *fields){
        qreal rowWidth = metrics.width(field->toString());
        maxWidth = std::max(rowWidth, maxWidth);
    }
    return maxWidth;
}

QRectF UMLClass::outlineRect() const
{
    const int padding = 12;
    QFontMetricsF metrics{qApp->font()};
    QSet<UMLFieldData *> *fields = umlClassData->getFields();
    QSet<UMLMethodData *> *methods = umlClassData->getMethods();
    QRectF rect = QRectF(0, 0, maxTextWidth(), (metrics.height())*(fields->size() + methods->size() + 1) + 10);
    rect.adjust(-padding, -padding, +padding, +padding);
    return rect;
}
