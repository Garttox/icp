#include <QtGui>
#include <QStyleOptionGraphicsItem>
#include <algorithm>

#include "umlclass.h"

#include "editclassdialog.h"
#include "ui_editclassdialog.h"

UMLClass::UMLClass(UMLClassData *umlClassData) : umlClassData(umlClassData)
{
    textColor = Qt::black;
    outlineColor = Qt::darkBlue;
    selectedOutlineColor = QColor(21, 193, 232);
    backgroundColor = Qt::white;
    setFlags(ItemIsMovable | ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);

    setPos(umlClassData->getPosX(), umlClassData->getPosY());
}

void UMLClass::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget * /* widget */)
{
    QPen pen;
    if (option->state & QStyle::State_Selected)
    {
        //pen.setStyle(Qt::DotLine);
        pen = QPen(selectedOutlineColor);
    }
    else
    {
        pen = QPen(outlineColor);
    }
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(backgroundColor);
    QRectF rect = outlineRect();
    painter->drawRect(rect);
    painter->setPen(textColor);

    QFontMetricsF metrics{qApp->font()};
    //painter->drawText(rect, Qt::AlignCenter, umlClassData->getName());
    QList<UMLFieldData *> fields = umlClassData->getFields();
    QList<UMLMethodData *> methods = umlClassData->getMethods();
    QPointF point = rect.topLeft();
    qreal offsetX = 3.0;
    point.setY(point.y() + metrics.height());
    point.setX(point.x() + offsetX);

    // class name
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(point, umlClassData->getDisplayName());
    font.setBold(false);
    painter->setFont(font);
    point.setY(point.y() + metrics.height()/2);
    point.setX(point.x() - offsetX);
    painter->drawLine(point, QPointF(point.x() + rect.width(), point.y()));
    point.setX(point.x() + offsetX);
    point.setY(point.y() + metrics.height());

    // fields
    foreach(auto *field, fields)
    {
        painter->drawText(point, field->toString());
        point.setY(point.y() + metrics.height());
    }

    // separator
    point.setX(point.x() - offsetX);
    point.setY(point.y() - metrics.height()/2);
    painter->drawLine(point, QPointF(point.x() + rect.width(), point.y()));
    point.setX(point.x() + offsetX);
    point.setY(point.y() + metrics.height());

    // methods
    foreach(auto *method, methods)
    {
        painter->drawText(point, method->toString());
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

void UMLClass::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/)
{
    EditClassDialog *editClassDialog = new EditClassDialog(umlClassData);
    editClassDialog->show();
}

qreal UMLClass::maxTextWidth() const
{
    QFontMetricsF metrics{qApp->font()};
    QList<UMLFieldData *> fields = umlClassData->getFields();
    QList<UMLMethodData *> methods = umlClassData->getMethods();
    qreal maxWidth = std::max(metrics.width(umlClassData->getDisplayName()), MIN_WIDTH);

    foreach(auto *method, methods)
    {
        qreal rowWidth = metrics.width(method->toString());
        maxWidth = std::max(rowWidth, maxWidth);
    }

    foreach(auto *field, fields)
    {
        qreal rowWidth = metrics.width(field->toString());
        maxWidth = std::max(rowWidth, maxWidth);
    }
    return maxWidth;
}

QRectF UMLClass::outlineRect() const
{
    const int padding = 12;
    QFontMetricsF metrics{qApp->font()};
    QList<UMLFieldData *> fields = umlClassData->getFields();
    QList<UMLMethodData *> methods = umlClassData->getMethods();
    QRectF rect = QRectF(0, 0, maxTextWidth() + padding, (metrics.height())*(fields.size() + methods.size()) + padding);
    rect.adjust(-padding, -padding, +padding, +padding);
    return rect;
}
