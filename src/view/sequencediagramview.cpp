#include "sequencediagramview.h"

#include <view/classes/umlclass.h>
#include <model/umlclassdata.h>
#include <model/umlclasstype.h>
#include <QMouseEvent>
#include <view/sequence/umlcall.h>

SequenceDiagramView::SequenceDiagramView(QWidget* parent, UMLSequenceData *umlSequenceData)
    : QGraphicsView(parent), umlSequenceData(umlSequenceData)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);

    connect(umlSequenceData, &UMLSequenceData::instanceModelAdded, this, &SequenceDiagramView::onInstanceModelAdded);
    connect(umlSequenceData, &UMLSequenceData::callModelAdded, this, &SequenceDiagramView::onCallModelAdded);
    drawBackgroundTiles();

}

UMLSequenceData *SequenceDiagramView::getUMLSequenceData() const
{
    return this->umlSequenceData;
}

// - - - - - private slots - - - - -


void SequenceDiagramView::onInstanceModelAdded(UMLInstanceData *umlInstanceData)
{
    addUMLInstance(umlInstanceData);
}

void SequenceDiagramView::onCallModelAdded(UMLCallData *umlCallData)
{
    addUMLCall(umlCallData);
}

// - - - - - private - - - - -

void SequenceDiagramView::drawBackgroundTiles()
{
    QPixmap pixmap(TILE_SIZE, TILE_SIZE);
    QPainter painter(&pixmap);
    pixmap.fill(Qt::white);
    painter.setPen(TILE_COLOR);
    painter.drawRect(0, 0, TILE_SIZE, TILE_SIZE);
    painter.end();
    setBackgroundBrush(pixmap);
}

void SequenceDiagramView::addUMLInstance(UMLInstanceData *umlInstanceData)
{
    UMLInstance *umlInstance = new UMLInstance(umlInstanceData, umlSequenceData);
    scene()->addItem(umlInstance);
}

void SequenceDiagramView::addUMLCall(UMLCallData *umlCallData)
{
    UMLInstance* sourceInstance = getUMLInstance(umlCallData->getSource());
    UMLInstance* destinationInstance = getUMLInstance(umlCallData->getDestination());
    UMLCall *umlCall = new UMLCall(umlCallData, sourceInstance, destinationInstance);
    scene()->addItem(umlCall);
}

UMLInstance *SequenceDiagramView::getUMLInstance(UMLInstanceData *umlInstanceData)
{
    QList<UMLInstance*> umlInstances = getItemsOfType<UMLInstance*>();
    foreach (auto umlInstance, umlInstances)
    {
        if (umlInstance->correspondsTo(umlInstanceData))
        {
            return umlInstance;
        }
    }
    return nullptr;
}

template<class T>
QList<T> SequenceDiagramView::getItemsOfType()
{
    QList<T> filtered;
    foreach(QGraphicsItem *item, scene()->items())
    {
        if (T casted = dynamic_cast<T>(item))
        {
            filtered.append(casted);
        }
    }
    return filtered;
}

void SequenceDiagramView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton)
    {
        originX = event->x();
        originY = event->y();
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void SequenceDiagramView::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::MidButton)
    {
        QPointF oldPoint = mapToScene(originX, originY);
        QPointF newPoint = mapToScene(event->pos());
        QPointF translation = newPoint - oldPoint;

        translate(translation.x(), translation.y());
        originX = event->x();
        originY = event->y();
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }
}
