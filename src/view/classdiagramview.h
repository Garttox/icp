#ifndef CLASSDIAGRAMVIEW_H
#define CLASSDIAGRAMVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWidget>
#include "classes/umlclass.h"
#include "model/umlclassdata.h"
#include "model/umldata.h"

class ClassDiagramView : public QGraphicsView
{
    Q_OBJECT

public:
    ClassDiagramView(QWidget* parent);

private slots:
    void classModelAdded(UMLClassData *classData);
    void relationModelAdded(UMLRelationData *relationData);
    void umlModelCleared();

private:
    UMLClass *getUMLClass(UMLClassData *umlClassData);
    void drawBackgroundTiles();
    void addUMLClass(UMLClassData *classData);
    void addUMLRelation(UMLRelationData *relationData);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    int originX;
    int originY;

    static constexpr qreal TILE_SIZE = 60;
    static constexpr QColor TILE_COLOR = QColor(225, 225, 225);
};

#endif // CLASSDIAGRAMVIEW_H
