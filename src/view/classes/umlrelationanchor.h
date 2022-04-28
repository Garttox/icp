#ifndef UMLRELATIONANCHOR_H
#define UMLRELATIONANCHOR_H

#include <QPen>
#include <QGraphicsEllipseItem>
#include <QVariant>

class UMLClass;

class UMLRelationAnchor : public QGraphicsEllipseItem
{
public:
    UMLRelationAnchor(qreal relX, qreal relY, UMLClass* parent);
    void setPositionRelativeToParent();

signals:
    void anchorDragged(UMLRelationAnchor *anchor, QPointF endpoint);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QRectF getRelativeRect() const;
    void setColorPen();
    void setDragLineProperties();

    QGraphicsLineItem dragLine;
    QPen dragLinePen;
    const qreal relX;
    const qreal relY;

    static constexpr QColor BRUSH_COLOR = QColor(255, 255, 255, 200);
    static constexpr QColor OUTLINE_COLOR = QColor(21, 193, 232, 140);
    static constexpr QColor DRAGLINE_COLOR = QColor(120, 120, 130);
    static constexpr qreal SIZE = 8;
};

#endif // UMLRELATIONANCHOR_H
