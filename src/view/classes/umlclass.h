#ifndef UMLCLASS_H
#define UMLCLASS_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>
#include <QEvent>
#include <QVariant>
#include "model\umldata.h"
#include "model\umlclassdata.h"
#include "umlrelationanchor.h"
#include "umlrelation.h"


class UMLClass : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    UMLClass(UMLClassData *umlClassData);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    bool correspondsTo(UMLClassData *umlClassData);
    UMLRelationAnchor *getAnchorById(int id) const;
    void remove();

private slots:
    void modelChanged();
    void onAnchorDragged(UMLRelationAnchor *anchor, QPointF endpoint);
    void onAnchorDragReleased(UMLRelationAnchor *source, UMLRelationAnchor *destination);

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
    static constexpr qreal ANCHOR_DRAG_OFFSET = 15;
};

#endif // UMLCLASS_H
