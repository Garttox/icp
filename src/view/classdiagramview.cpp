/**
 * ICP - UML Application
 * @date 24/4/2022
 * @file classdiagramview.cpp
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#include <QDebug>

#include "classdiagramview.h"
#include "model/dataprovider.h"
#include "model/umlclassdata.h"
#include "model/umldata.h"
#include "view/classes/umlclass.h"
#include "classtoolbar.h"
#include "classes/umlclassnotifier.h"

ClassDiagramView::ClassDiagramView(QWidget* parent)
    : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);
    drawBackgroundTiles();

    UMLData* umlData = DataProvider::getInstance().getUMLData();
    connect(umlData, &UMLData::classModelAdded, this, &ClassDiagramView::onClassModelAdded);
    connect(umlData, &UMLData::classModelRemoved, this, &ClassDiagramView::onClassModelRemoved);
    connect(umlData, &UMLData::relationModelAdded, this, &ClassDiagramView::onRelationModelAdded);
    connect(umlData, &UMLData::relationModelRemoved, this, &ClassDiagramView::onRelationModelRemoved);
    connect(umlData, &UMLData::umlModelCleared, this, &ClassDiagramView::onUmlModelCleared);
}

QPixmap ClassDiagramView::getViewportPixmap()
{
    QRect crop(0, 0, width(),height());
    QPixmap pixmap = grab(crop);
    return pixmap;
}

void ClassDiagramView::addUMLClass(UMLClassData *umlClassData)
{
    UMLClass *umlClass = new UMLClass(umlClassData);
    scene()->addItem(umlClass);
}

void ClassDiagramView::removeUMLClass(UMLClass *umlClass)
{
    removeRelationConnectedTo(umlClass);
    emit UMLClassNotifier::getInstance()->classRemoved(umlClass);
    scene()->removeItem(umlClass);
    delete umlClass;
}

void ClassDiagramView::removeUMLClass(UMLClassData *umlClassData)
{
    UMLClass *umlClass = getUMLClass(umlClassData);
    if (umlClass != nullptr)
    {
        removeUMLClass(umlClass);
    }
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
    }
    else
    {
        // inconsistency
    }
}

void ClassDiagramView::removeUMLRelation(UMLRelation *umlRelation)
{
    emit UMLClassNotifier::getInstance()->relationRemoved(umlRelation);
    scene()->removeItem(umlRelation);
    delete umlRelation;
}

void ClassDiagramView::removeUMLRelation(UMLRelationData *umlRelationData)
{
    UMLRelation *umlRelation = getUMLRelation(umlRelationData);
    if (umlRelation != nullptr)
    {
        removeUMLRelation(umlRelation);
    }
}

// - - - - - private slots - - - - -

void ClassDiagramView::onClassModelAdded(UMLClassData *umlClassData)
{
    addUMLClass(umlClassData);
}

void ClassDiagramView::onClassModelRemoved(UMLClassData *umlClassData)
{
    removeUMLClass(umlClassData);
}

void ClassDiagramView::onRelationModelAdded(UMLRelationData *umlRelationData)
{
    addUMLRelation(umlRelationData);
}

void ClassDiagramView::onRelationModelRemoved(UMLRelationData *umlRelationData)
{
    removeUMLRelation(umlRelationData);
}

void ClassDiagramView::onUmlModelCleared()
{
    scene()->clear();
}

// - - - - - private - - - - -

UMLClass *ClassDiagramView::getUMLClass(UMLClassData *umlClassData)
{
    QList<UMLClass*> umlClasses = getItemsOfType<UMLClass*>();
    foreach (auto umlClass, umlClasses)
    {
        if (umlClass->correspondsTo(umlClassData))
        {
            return umlClass;
        }
    }
    return nullptr;
}

UMLRelation *ClassDiagramView::getUMLRelation(UMLRelationData *umlRelationData)
{
    QList<UMLRelation*> umlRelations = getItemsOfType<UMLRelation*>();
    foreach (auto umlRelation, umlRelations)
    {
        if (umlRelation->correspondsTo(umlRelationData))
        {
            return umlRelation;
        }
    }
    return nullptr;
}

template<class T>
QList<T> ClassDiagramView::getItemsOfType()
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

void ClassDiagramView::removeRelationConnectedTo(UMLClass *umlClass)
{
    foreach (auto umlRelation, getItemsOfType<UMLRelation*>())
    {
        if (umlRelation->isConnectedToUMLClass(umlClass))
        {
            removeUMLRelation(umlRelation);
        }
    }
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

