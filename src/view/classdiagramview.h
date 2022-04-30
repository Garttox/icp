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
    void setAndApplyZoom(qreal zoom);
    void addUMLClass(UMLClassData *classData);
    void addUMLRelation(UMLRelationData *relationData);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    int originX;
    int originY;
    qreal zoom = 1;

    static constexpr qreal ZOOM_MIN = 0.8;
    static constexpr qreal ZOOM_MAX = 1.2;
    static constexpr qreal ZOOM_STEP = 0.05;
    static constexpr qreal TILE_SIZE = 60;
    static constexpr QColor TILE_COLOR = QColor(225, 225, 225);
};

#endif // CLASSDIAGRAMVIEW_H
