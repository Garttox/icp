#ifndef UMLCALLARROW_H
#define UMLCALLARROW_H

#include <QApplication>
#include <QObject>
#include <QGraphicsLineItem>
#include <QFont>
#include <QString>

class UMLCall;

class UMLCallArrow : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    UMLCallArrow(UMLCall *parent);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    void setCorrectPosition();
    void setArrowHead();
    void drawArrowHead(QPainter *painter);
    QString getMethodDisplayName() const;

    QFont TEXT_FONT = QFont(qApp->font().family(), 9, QFont::Normal);
    static constexpr qreal ARROW_SIZE = 10;
    QPolygonF arrowHead;
};

#endif // UMLCALLARROW_H
