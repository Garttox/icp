#ifndef CLASSDIAGRAMGRAPHICSVIEW_H
#define CLASSDIAGRAMGRAPHICSVIEW_H

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

    void drawBackgroundTiles();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    static constexpr qreal TILE_SIZE = 60;
    static constexpr QColor TILE_COLOR = QColor(220, 220, 220);
};

#endif // CLASSDIAGRAMGRAPHICSVIEW_H
