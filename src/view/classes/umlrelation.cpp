/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umlrelation.cpp
 * @author Martin Bednář (xbedna77)
 */

#include <QGraphicsScene>
#include <QDebug>
#include <QtMath>
#include "model/dataprovider.h"
#include "umlrelation.h"
#include "umlclass.h"
#include "umlclassnotifier.h"
#include "view/classes/editrelationdialog.h"
#include "ui_editrelationdialog.h"

UMLRelation::UMLRelation(UMLRelationData* relation, UMLRelationAnchor* sourceAnchor, UMLRelationAnchor* destinationAnchor) :
    QObject(), QGraphicsLineItem(),
    umlRelationData(relation),
    sourceAnchor(sourceAnchor),
    destinationAnchor(destinationAnchor)
{
    setCorrectPosition();
    setFlag(ItemIsSelectable);
    setZValue(-1);
    connect(UMLClassNotifier::getInstance(), SIGNAL(anchorRemoved(UMLRelationAnchor*)),
            this, SLOT(onAnchorRemoved(UMLRelationAnchor*)));
}

QRectF UMLRelation::boundingRect() const
{
    QPointF p1 = line().p1();
    QPointF p2 = line().p2();
    qreal offset = ARROW_SIZE / 2;
    QSizeF size(p2.x() - p1.x(), p2.y() - p1.y());

    return QRectF(p1, size)
        .normalized()
        .adjusted(-offset, -offset, offset, offset);
}

QPainterPath UMLRelation::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

bool UMLRelation::isOfType(UMLRelationType umlRelationType)
{
    return umlRelationData->getType() == umlRelationType;
}

void UMLRelation::remove()
{
    scene()->removeItem(this);
    DataProvider::getInstance().getUMLData()->removeRelation(umlRelationData);
    delete this;
}

// - - - - - protected - - - - -

void UMLRelation::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * /*event*/)
{
    EditRelationDialog dialog(umlRelationData);
    dialog.exec();
}

void UMLRelation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setCorrectPosition();

    // disable default outline on select
    QStyleOptionGraphicsItem myOption(*option);
    myOption.state &= ~QStyle::State_Selected;

    // draw line
    setPen(getColorPen());
    QGraphicsLineItem::paint(painter, &myOption, widget);


    // draw arrow head
    createArrowHeadPolygon();
    drawArrowHead(painter);
}

// - - - - - private slots - - - - -

void UMLRelation::onAnchorRemoved(UMLRelationAnchor *anchor)
{
    if (anchor == sourceAnchor || anchor == destinationAnchor)
    {
        remove();
    }
}

// - - - - - private - - - - -

QPen UMLRelation::getColorPen() const
{
    QPen pen;
    bool selected = isSelected();
    pen.setWidth(selected ? 3 : 2);
    pen.setColor(selected ? SELECT_COLOR : NORMAL_COLOR);
    return pen;
}


void UMLRelation::setCorrectPosition()
{
    QPointF sourcePoint = sourceAnchor->sceneBoundingRect().center();
    QPointF destinationPoint = destinationAnchor->sceneBoundingRect().center();
    setLine(sourcePoint.x(), sourcePoint.y(), destinationPoint.x(), destinationPoint.y());
}

void UMLRelation::createArrowHeadPolygon()
{
    arrowHead.clear();

    if (isOfType(UMLRelationType::ASSOCIATION))
    {
        return; // Association has no arrow head
    }

    qreal angle = line().angle();
    qreal x = line().p2().x();
    qreal y = line().p2().y();

    arrowHead.append(QPoint(x - ARROW_SIZE, y - (ARROW_SIZE  / 2)));
    arrowHead.append(QPoint(x, y));
    arrowHead.append(QPoint(x - ARROW_SIZE, y + (ARROW_SIZE  / 2)));
    if (isOfType(UMLRelationType::COMPOSITION) || isOfType(UMLRelationType::AGREGATION))
    {
        arrowHead.append(QPoint(x - (ARROW_SIZE * 2), y));
    }

    arrowHead = QTransform()
        .translate(x, y)
        .rotate(-angle)
        .translate(-x, -y)
        .map(arrowHead);
}

void UMLRelation::drawArrowHead(QPainter *painter)
{
    QPainterPath path;
    QColor fillColor = isOfType(UMLRelationType::COMPOSITION) ? getColorPen().color() : Qt::white;
    path.addPolygon(arrowHead);
    painter->fillPath(path, fillColor);
    painter->drawPolygon(arrowHead);
}
