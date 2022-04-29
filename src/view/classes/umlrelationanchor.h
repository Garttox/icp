#ifndef UMLRELATIONANCHOR_H
#define UMLRELATIONANCHOR_H

#include <QPen>
#include <QGraphicsEllipseItem>

class UMLClass;

class UMLRelationAnchor : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    UMLRelationAnchor(UMLClass* parent, const int id, qreal relX, qreal relY);
    void setPositionRelativeToParent();
    QRectF getSceneRect() const;
    QRectF getRelativeRect() const;
    int getId() const;
    void remove();

signals:
    void anchorDragged(UMLRelationAnchor *anchor, QPointF endpoint);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private slots:
    void onClassRemoved(UMLClass* umlClass);

private:
    void setColorPen();
    void setDragLineProperties();

    QGraphicsLineItem dragLine;
    QPen dragLinePen;
    const int id;
    const qreal relX;
    const qreal relY;

    static constexpr QColor BRUSH_COLOR = QColor(255, 255, 255, 0);
    static constexpr QColor OUTLINE_COLOR = QColor(20, 120, 160, 90);
    static constexpr QColor DRAGLINE_COLOR = QColor(21, 193, 232);
    static constexpr qreal SIZE = 9;
};

#endif // UMLRELATIONANCHOR_H
