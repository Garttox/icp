#ifndef UMLCLASS_H
#define UMLCLASS_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>

#include "model\umldata.h"
#include "model\umlclassdata.h"
#include "umlrelationanchor.h"
#include "qevent.h"

class UMLClass : public QGraphicsItem
{
public:
    UMLClass(UMLClassData *umlClassData);
    ~UMLClass();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void freeClassData();
    void registerAnchorDragged(UMLRelationAnchor *anchor, QPointF endpoint);
    QRectF boundingRect() const override;
    QList<UMLRelationAnchor *> getAnchors() const;

public slots:
    void modelChanged();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    QRectF outlineRect() const;
    qreal maxTextWidth() const;
    void addRelationAnchors();
    void resetAnchorsPositions();
    void setAnchorsVisible(bool enabled);

    QColor textColor;
    QColor backgroundColor;
    QColor outlineColor;
    QColor selectedOutlineColor;
    UMLClassData *umlClassData;
    QList<UMLRelationAnchor *> anchors;

    static constexpr qreal MIN_WIDTH = 60;
};

#endif // UMLCLASS_H
