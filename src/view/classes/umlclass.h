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
    QRectF boundingRect() const override;
    bool correspondsTo(UMLClassData *umlClassData);
    UMLRelationAnchor *getAnchorById(int id) const;
    UMLClassData *getUMLClassData() const;
    int getAnchorId(UMLRelationAnchor *anchor);
    void remove();

private slots:
    void onRelationModelAdded(UMLRelationData *relationData);
    void onAnchorDragged(UMLRelationAnchor *anchor, QPointF endpoint);
    void onAnchorDragReleased(UMLRelationAnchor *source, UMLRelationAnchor *destination);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QRectF outlineRect() const;
    qreal maxTextWidth() const;
    void addRelationAnchors();
    void resetAnchorsPositions();
    void setAnchorsVisible(bool enabled);
    void addRelationDataToModel(UMLRelationAnchor *source, UMLRelationAnchor *destination);

    QColor textColor;
    QColor backgroundColor;
    QColor outlineColor;
    QColor selectedOutlineColor;
    UMLClassData *umlClassData;
    QList<UMLRelationAnchor *> anchors;

    static constexpr qreal MIN_WIDTH = 60;
    static constexpr qreal ANCHOR_DRAG_OFFSET = 15;
    static constexpr QColor HIGHLIGHT_COLOR = QColor(0, 100, 140);
};

#endif // UMLCLASS_H
