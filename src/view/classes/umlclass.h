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

class UMLClass : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    UMLClass(UMLClassData *umlClassData);
    ~UMLClass();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void freeClassData();
    QRectF boundingRect() const override;
    QList<UMLRelationAnchor *> getAnchors() const;

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
