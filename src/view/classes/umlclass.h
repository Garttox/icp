#ifndef UMLCLASS_H
#define UMLCLASS_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>

class UMLData;
class UMLClassData;

class UMLClass : public QGraphicsItem
{
public:
    UMLClass(UMLClassData *umlClassData);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
public slots:
    void modelChanged();
private:
    QColor myTextColor;
    QColor myBackgroundColor;
    QColor myOutlineColor;

    QRectF outlineRect() const;
    qreal maxTextWidth() const;

    UMLClassData *umlClassData;
};

#endif // UMLCLASS_H
