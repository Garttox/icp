#include "sequencediagramview.h"

#include <view/classes/umlclass.h>
#include <model/umlclassmodel.h>
#include <model/umlclasstype.h>
#include <QMouseEvent>
#include <view/sequence/umlcall.h>

SequenceDiagramView::SequenceDiagramView(QWidget* parent, UMLSequenceModel *umlSequenceModel)
    : QGraphicsView(parent), umlSequenceModel(umlSequenceModel)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);

    connect(umlSequenceModel, &UMLSequenceModel::instanceModelAdded, this, &SequenceDiagramView::onInstanceModelAdded);
    connect(umlSequenceModel, &UMLSequenceModel::instanceModelRemoved, this, &SequenceDiagramView::onInstanceModelRemoved);
    connect(umlSequenceModel, &UMLSequenceModel::callModelAdded, this, &SequenceDiagramView::onCallModelAdded);
    connect(umlSequenceModel, &UMLSequenceModel::callModelRemoved, this, &SequenceDiagramView::onCallModelRemoved);


    drawBackgroundTiles();
}

bool SequenceDiagramView::correspondsTo(UMLSequenceModel *umlSequenceModel)
{
    return this->umlSequenceModel == umlSequenceModel;
}

UMLSequenceModel *SequenceDiagramView::getUMLSequenceModel() const
{
    return this->umlSequenceModel;
}

void SequenceDiagramView::loadSequence()
{
    foreach(auto *umlInstanceModel, umlSequenceModel->getInstances())
    {
        addUMLInstance(umlInstanceModel);
    }

    foreach(auto *umlCallModel, umlSequenceModel->getCalls())
    {
        addUMLCall(umlCallModel);
    }
}

// - - - - - private slots - - - - -


void SequenceDiagramView::onInstanceModelAdded(UMLInstanceModel *umlInstanceModel)
{
    addUMLInstance(umlInstanceModel);
}

void SequenceDiagramView::onInstanceModelRemoved(UMLInstanceModel *umlInstanceModel)
{
    removeUMLInstance(umlInstanceModel);
}


void SequenceDiagramView::onCallModelAdded(UMLCallModel *umlCallModel)
{
    addUMLCall(umlCallModel);
}

void SequenceDiagramView::onCallModelRemoved(UMLCallModel *umlCallModel)
{
    removeUMLCall(umlCallModel);
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

void SequenceDiagramView::addUMLInstance(UMLInstanceModel *umlInstanceModel)
{
    UMLInstance *umlInstance = new UMLInstance(umlInstanceModel, umlSequenceModel);
    scene()->addItem(umlInstance);
}

void SequenceDiagramView::addUMLCall(UMLCallModel *umlCallModel)
{
    UMLInstance* sourceInstance = getUMLInstance(umlCallModel->getSource());
    UMLInstance* destinationInstance = getUMLInstance(umlCallModel->getDestination());
    new UMLCall(umlCallModel, sourceInstance, destinationInstance);
}

void SequenceDiagramView::removeUMLInstance(UMLInstanceModel *umlInstanceModel)
{
    UMLInstance *umlInstance = getUMLInstance(umlInstanceModel);
    scene()->removeItem(umlInstance);
    delete umlInstance;
}

void SequenceDiagramView::removeUMLCall(UMLCallModel *umlCallModel)
{
    UMLCall *umlCall = getUMLCall(umlCallModel);
    scene()->removeItem(umlCall);
    delete umlCall;
}

UMLInstance *SequenceDiagramView::getUMLInstance(UMLInstanceModel *umlInstanceModel)
{
    QList<UMLInstance*> umlInstances = getItemsOfType<UMLInstance*>();
    foreach (auto umlInstance, umlInstances)
    {
        if (umlInstance->correspondsTo(umlInstanceModel))
        {
            return umlInstance;
        }
    }
    return nullptr;
}

UMLCall *SequenceDiagramView::getUMLCall(UMLCallModel *umlCallModel)
{
    QList<UMLCall*> umlCalls = getItemsOfType<UMLCall*>();
    foreach (auto umlCall, umlCalls)
    {
        if (umlCall->correspondsTo(umlCallModel))
        {
            return umlCall;
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
