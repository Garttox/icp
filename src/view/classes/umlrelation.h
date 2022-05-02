/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umlrelation.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef UMLRELATION_H
#define UMLRELATION_H

#include <QGraphicsLineItem>
#include <QPainter>
#include "model/umlrelationdata.h"
#include "umlrelationanchor.h"

class UMLClass;

/**
 * @brief Graphical object for displaying relation between UMLClasses.
 * @author Martin Bednář (xbedna77)
 */
class UMLRelation : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    UMLRelation(UMLRelationData* relation, UMLRelationAnchor* sourceAnchor, UMLRelationAnchor* destinationAnchor);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    
    /**
     * @brief Checks, if relation (resp. underlying UMLRelationData) is of given relation type.
     * @param umlRelationType Type of the relation to check.
     * @return True if relation is of given type, false otherwise.
     */
    bool isOfType(UMLRelationType umlRelationType);
    
    /**
     * @brief Removes the relation from the scene and deletes it's data.
     */
    void remove();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private slots:
    void onAnchorRemoved(UMLRelationAnchor *anchor);

private:
    QPen getColorPen() const;
    void setCorrectPosition();
    void createArrowHeadPolygon();
    void drawArrowHead(QPainter *painter);

    QPolygonF arrowHead;
    UMLRelationData *umlRelationData;
    const UMLRelationAnchor *sourceAnchor;
    const UMLRelationAnchor *destinationAnchor;
    static constexpr qreal ARROW_SIZE = 14;
    QColor SELECT_COLOR = QColor(100, 170, 125);
    QColor NORMAL_COLOR = QColor(100, 115, 120);
};

#endif // UMLRELATION_H
