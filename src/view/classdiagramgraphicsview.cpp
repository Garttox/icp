#include <QDebug>

#include "classdiagramgraphicsview.h"
#include "model\dataprovider.h"
#include "model\umlclassdata.h"
#include "model\umldata.h"

#include "view\classes\umlclass.h"


ClassDiagramGraphicsView::ClassDiagramGraphicsView(QWidget* parent)
    : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);
    UMLData* umlData = DataProvider::getInstance().getUMLData();
    connect(umlData, SIGNAL(classModelAdded(UMLClassData*)), this, SLOT(classModelAdded(UMLClassData*)));
    connect(umlData, SIGNAL(umlModelCleared()), this, SLOT(umlModelCleared()));
}

void ClassDiagramGraphicsView::classModelAdded(UMLClassData *classData)
{
    UMLClass *umlClass = new UMLClass(classData);
    scene()->addItem(umlClass);
}

void ClassDiagramGraphicsView::umlModelCleared()
{
    scene()->clear();
}

void ClassDiagramGraphicsView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton)
    {
        originX = event->x();
        originY = event->y();
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void ClassDiagramGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::MidButton)
    {
        QPointF oldPoint = mapToScene(originX, originY);
        QPointF newPoint = mapToScene(event->pos());
        QPointF translation = newPoint - oldPoint;

        translate(translation.x(), translation.y());
        originX = event->x();
        originY = event->y();
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}
