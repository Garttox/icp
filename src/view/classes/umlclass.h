#ifndef UMLCLASS_H
#define UMLCLASS_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>

#include "model\umldata.h"
#include "model\umlclassdata.h"
#include "qevent.h"

class UMLClass : public QGraphicsItem
{
public:
    UMLClass(UMLClassData *umlClassData);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
public slots:
    void modelChanged();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor textColor;
    QColor backgroundColor;
    QColor outlineColor;
    QColor selectedOutlineColor;

    const qreal MIN_WIDTH = 60;

    QRectF outlineRect() const;
    qreal maxTextWidth() const;

    UMLClassData *umlClassData;
};

#endif // UMLCLASS_H
