#ifndef UMLRELATION_H
#define UMLRELATION_H

#include <QGraphicsLineItem>
#include <QPainter>
#include "model/umlrelationdata.h"
#include "umlrelationanchor.h"

class UMLClass;


class UMLRelation : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    UMLRelation(UMLRelationData* relation, UMLRelationAnchor* sourceAnchor, UMLRelationAnchor* destinationAnchor);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    bool isOfType(UMLRelationType umlRelationType);
    void remove();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private slots:
    void onAnchorRemoved(UMLRelationAnchor *anchor);

private:
    void setColorPen();
    void setCorrectPosition();
    void createArrowHeadPolygon();
    void drawArrowHead(QPainter *painter);

    QPolygonF arrowHead;
    UMLRelationData *umlRelationData;
    const UMLRelationAnchor *sourceAnchor;
    const UMLRelationAnchor *destinationAnchor;
    static constexpr qreal ARROW_SIZE = 14;
    static constexpr QColor LINE_COLOR = QColor(100, 115, 120);
};

#endif // UMLRELATION_H
