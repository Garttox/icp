/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlcallarrow.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef UMLCALLARROW_H
#define UMLCALLARROW_H

#include "umlcallarrowtype.h"

#include <QApplication>
#include <QObject>
#include <QGraphicsLineItem>
#include <QFont>
#include <QString>

class UMLCall;

/**
 * @brief Graphical object for displaying UML Call arrow.
 * @author Michal Trlica (xtrlic02)
 */
class UMLCallArrow : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    UMLCallArrow(UMLCall *parent, UMLCallArrowType arrowType);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void setCorrectPosition();
    void setArrowHead();
    void drawArrowHead(QPainter *painter);
    QString getMethodDisplayText() const;

    QFont TEXT_FONT = QFont(qApp->font().family(), 9, QFont::Normal);
    static constexpr qreal ARROW_SIZE = 10;
    QPolygonF arrowHead;
    UMLCallArrowType arrowType;
};

#endif // UMLCALLARROW_H
