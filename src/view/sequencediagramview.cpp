#include "sequencediagramview.h"

#include <view/classes/umlclass.h>
#include <model/umlclassdata.h>
#include <model/umlclasstype.h>
#include <QMouseEvent>
#include <view/sequence/umlinstance.h>



SequenceDiagramView::SequenceDiagramView(QWidget* parent, UMLSequenceData *umlSequenceData)
    : QGraphicsView(parent), umlSequenceData(umlSequenceData)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);

    connect(umlSequenceData, &UMLSequenceData::instanceModelAdded, this, &SequenceDiagramView::onInstanceModelAdded);

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
    UMLInstance *umlInstance = new UMLInstance(umlInstanceData);
    scene()->addItem(umlInstance);
    qDebug() << "added";
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
