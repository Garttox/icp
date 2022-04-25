#ifndef UMLCLASS_H
#define UMLCLASS_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>

class UMLClass : public QGraphicsItem
{
public:
    UMLClass();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    QString myText;
    QColor myTextColor;
    QColor myBackgroundColor;
    QColor myOutlineColor;

    QRectF outlineRect() const;
};

#endif // UMLCLASS_H
