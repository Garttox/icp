#ifndef UMLINSTANCELIFELINE_H
#define UMLINSTANCELIFELINE_H

#include <QGraphicsLineItem>

class UMLInstance;

class UMLInstanceLifeLine : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    UMLInstanceLifeLine(UMLInstance *parent);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void setCorrectPosition();
    void setPenStyle();

    static constexpr qreal DETECTION_RADIUS = 15;
    QColor LINE_COLOR = QColor(Qt::black);
};

#endif // UMLINSTANCELIFELINE_H
