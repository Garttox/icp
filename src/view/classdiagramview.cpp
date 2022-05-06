/**
 * ICP - UML Application
 * @date 24/4/2022
 * @file classdiagramview.cpp
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#include <QDebug>

#include "classdiagramview.h"
#include "model/modelprovider.h"
#include "model/umlclassmodel.h"
#include "model/umlmodel.h"
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

    UMLModel* umlModel = ModelProvider::getInstance().getModel();
    connect(umlModel, &UMLModel::classModelAdded, this, &ClassDiagramView::onClassModelAdded);
    connect(umlModel, &UMLModel::classModelRemoved, this, &ClassDiagramView::onClassModelRemoved);
    connect(umlModel, &UMLModel::relationModelAdded, this, &ClassDiagramView::onRelationModelAdded);
    connect(umlModel, &UMLModel::relationModelRemoved, this, &ClassDiagramView::onRelationModelRemoved);
    connect(umlModel, &UMLModel::umlModelCleared, this, &ClassDiagramView::onUmlModelCleared);
}

QPixmap ClassDiagramView::getViewportPixmap()
{
    QRect crop(0, 0, width(),height());
    QPixmap pixmap = grab(crop);
    return pixmap;
}

void ClassDiagramView::addUMLClass(UMLClassModel *umlClassModel)
{
    UMLClass *umlClass = new UMLClass(umlClassModel);
    scene()->addItem(umlClass);
}

void ClassDiagramView::removeUMLClass(UMLClass *umlClass)
{
    removeRelationConnectedTo(umlClass);
    emit UMLClassNotifier::getInstance()->classRemoved(umlClass);
    scene()->removeItem(umlClass);
    delete umlClass;
}

void ClassDiagramView::removeUMLClass(UMLClassModel *umlClassModel)
{
    UMLClass *umlClass = getUMLClass(umlClassModel);
    if (umlClass != nullptr)
    {
        removeUMLClass(umlClass);
    }
}

void ClassDiagramView::addUMLRelation(UMLRelationModel *umlRelationModel)
{
    UMLClass *source = getUMLClass(umlRelationModel->getSource());
    UMLClass *destination = getUMLClass(umlRelationModel->getDestination());
    if (source != nullptr && destination != nullptr)
    {
        UMLRelationAnchor *sourceAnchor = source->getAnchorById(umlRelationModel->getSourceAnchorId());
        UMLRelationAnchor *destinationAnchor = destination->getAnchorById(umlRelationModel->getDestinationAnchorId());
        if (sourceAnchor != nullptr && destinationAnchor != nullptr)
        {
            UMLRelation *relation = new UMLRelation(umlRelationModel, sourceAnchor, destinationAnchor);
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

void ClassDiagramView::removeUMLRelation(UMLRelationModel *umlRelationModel)
{
    UMLRelation *umlRelation = getUMLRelation(umlRelationModel);
    if (umlRelation != nullptr)
    {
        removeUMLRelation(umlRelation);
    }
}

// - - - - - private slots - - - - -

void ClassDiagramView::onClassModelAdded(UMLClassModel *umlClassModel)
{
    addUMLClass(umlClassModel);
}

void ClassDiagramView::onClassModelRemoved(UMLClassModel *umlClassModel)
{
    removeUMLClass(umlClassModel);
}

void ClassDiagramView::onRelationModelAdded(UMLRelationModel *umlRelationModel)
{
    addUMLRelation(umlRelationModel);
}

void ClassDiagramView::onRelationModelRemoved(UMLRelationModel *umlRelationModel)
{
    removeUMLRelation(umlRelationModel);
}

void ClassDiagramView::onUmlModelCleared()
{
    scene()->clear();
}

// - - - - - private - - - - -

UMLClass *ClassDiagramView::getUMLClass(UMLClassModel *umlClassModel)
{
    QList<UMLClass*> umlClasses = getItemsOfType<UMLClass*>();
    foreach (auto umlClass, umlClasses)
    {
        if (umlClass->correspondsTo(umlClassModel))
        {
            return umlClass;
        }
    }
    return nullptr;
}

UMLRelation *ClassDiagramView::getUMLRelation(UMLRelationModel *umlRelationModel)
{
    QList<UMLRelation*> umlRelations = getItemsOfType<UMLRelation*>();
    foreach (auto umlRelation, umlRelations)
    {
        if (umlRelation->correspondsTo(umlRelationModel))
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

