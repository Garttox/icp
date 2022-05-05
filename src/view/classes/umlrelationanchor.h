/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umlrelationanchor.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLRELATIONANCHOR_H
#define UMLRELATIONANCHOR_H

#include <QPen>
#include <QGraphicsEllipseItem>

class UMLClass;

/**
 * @brief Graphical anchor connected to UMLClass, serving purpose of creating new relations by dragging.
 * @author Martin Bednář (xbedna77)
 */
class UMLRelationAnchor : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    UMLRelationAnchor(UMLClass* parent, qreal relX, qreal relY);
    
    /**
     * @brief Set the position relative to the parent object (UMLClass).
     */
    void setPositionRelativeToParent();
    
    /**
     * @brief Get scene bounding rect. Useful for drag/drop detection.
     * @return Scene bounding rect.
     */
    QRectF getSceneRect() const;
    
    /**
     * @brief Get bounding rect relative to the parent item (UMLClass).
     * @return Bounding rect relative to parent.
     */
    QRectF getRelativeRect() const;
    
    /**
     * @brief Get parent UMLClass object.
     * @return Parent UMLClass. 
     */
    UMLClass* getParentUMLClass() const;
    
    /**
     * @brief Get id of the anchor. Anchors ids are used for saving/loading.
     * @return Constant id of the anchor. 
     */
    int getId();

signals:
    void anchorDragged(UMLRelationAnchor *anchor, QPointF endpoint);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void setColorPen();
    void setDragLineProperties();

    QGraphicsLineItem dragLine;
    QPen dragLinePen;
    const qreal relX;
    const qreal relY;

    QColor BRUSH_COLOR = QColor(255, 255, 255, 0);
    QColor OUTLINE_COLOR = QColor(20, 120, 160, 90);
    QColor DRAGLINE_COLOR = QColor(21, 193, 232);
    static constexpr qreal SIZE = 9;
};

#endif // UMLRELATIONANCHOR_H
