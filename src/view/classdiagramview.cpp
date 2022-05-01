#include <QDebug>

#include "classdiagramview.h"
#include "model/dataprovider.h"
#include "model/umlclassdata.h"
#include "model/umldata.h"
#include "view/classes/umlclass.h"
#include "classtoolbar.h"

ClassDiagramView::ClassDiagramView(QWidget* parent)
    : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);
    UMLData* umlData = DataProvider::getInstance().getUMLData();
    connect(umlData, SIGNAL(classModelAdded(UMLClassData*)), this, SLOT(classModelAdded(UMLClassData*)));
    connect(umlData, SIGNAL(relationModelAdded(UMLRelationData*)), this, SLOT(relationModelAdded(UMLRelationData*)));
    connect(umlData, SIGNAL(umlModelCleared()), this, SLOT(umlModelCleared()));
    drawBackgroundTiles();
}

void ClassDiagramView::createToolBar()
{
    if (classToolBar == nullptr)
    {
        classToolBar = new ClassToolBar(this, scene());
    }
}

QPixmap ClassDiagramView::getViewportPixmap()
{
    classToolBar->setVisible(false);
    QRect crop(0, 0, width(),height());
    QPixmap pixmap = grab(crop);
    classToolBar->setVisible(true);
    return pixmap;
}

void ClassDiagramView::classModelAdded(UMLClassData *classData)
{
    addUMLClass(classData);
}

void ClassDiagramView::relationModelAdded(UMLRelationData *relationData)
{
    addUMLRelation(relationData);
}

void ClassDiagramView::umlModelCleared()
{
    scene()->clear();
}

UMLClass *ClassDiagramView::getUMLClass(UMLClassData *umlClassData)
{
    QList<QGraphicsItem *> graphicsItems = items();
    foreach (QGraphicsItem *graphicsItem, graphicsItems)
    {
        UMLClass *umlClass = dynamic_cast<UMLClass *>(graphicsItem);
        if (umlClass != nullptr && umlClass->correspondsTo(umlClassData))
        {
            return umlClass;
        }
    }
    return nullptr;
}

void ClassDiagramView::drawBackgroundTiles()
{
    QPixmap pixmap(TILE_SIZE, TILE_SIZE);
    QPainter painter(&pixmap);
    qreal third = TILE_SIZE / 3;
    qreal twoThirds = third * 2;
    pixmap.fill(Qt::white);
    painter.setPen(TILE_COLOR.lighter(108));
    painter.drawRect(0, 0, third, third);
    painter.drawRect(third, third, third, third);
    painter.drawRect(0, twoThirds, third, third);
    painter.drawRect(twoThirds, 0, third, third);
    painter.drawRect(twoThirds, twoThirds, third, third);
    painter.setPen(TILE_COLOR);
    painter.drawRect(0, 0, TILE_SIZE, TILE_SIZE);
    painter.end();
    setBackgroundBrush(pixmap);
}

void ClassDiagramView::addUMLClass(UMLClassData *classData)
{
    UMLClass *umlClass = new UMLClass(classData);
    scene()->addItem(umlClass);
}

void ClassDiagramView::addUMLRelation(UMLRelationData *relationData)
{
    UMLClass *source = getUMLClass(relationData->getSource());
    UMLClass *destination = getUMLClass(relationData->getDestination());
    if (source != nullptr && destination != nullptr)
    {
        UMLRelationAnchor *sourceAnchor = source->getAnchorById(relationData->getSourceAnchorId());
        UMLRelationAnchor *destinationAnchor = destination->getAnchorById(relationData->getDestinationAnchorId());
        if (sourceAnchor != nullptr && destinationAnchor != nullptr)
        {
            UMLRelation *relation = new UMLRelation(relationData, sourceAnchor, destinationAnchor);
            scene()->addItem(relation);
        }
        else
        {
            // data error
        }
    }
    else
    {
        // inconsistency
    }
}

void ClassDiagramView::mousePressEvent(QMouseEvent* event)
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

void ClassDiagramView::mouseMoveEvent(QMouseEvent* event)
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

