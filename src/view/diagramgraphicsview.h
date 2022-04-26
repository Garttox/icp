#ifndef DIAGRAMGRAPHICSVIEW_H
#define DIAGRAMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWidget>

#include "model\umlclassdata.h"
#include "model\umldata.h"

class ClassDiagramGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    ClassDiagramGraphicsView(QWidget* parent);
private slots:
    void classModelAdded(UMLClassData *classData);
    void umlModelCleared();
private:
    int originX;
    int originY;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // DIAGRAMGRAPHICSVIEW_H
