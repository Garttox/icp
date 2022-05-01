#ifndef UMLCLASS_H
#define UMLCLASS_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>
#include <QEvent>
#include <QVariant>
#include "model/umldata.h"
#include "model/umlclassdata.h"
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
    void onClassModelEdited(UMLClassData* umlClassData);
    void onRelationModelAdded(UMLRelationData *relationData);
    void onRelationModelEdited(UMLRelationData *relationData);
    void onRelationModelRemoved(UMLRelationData *relationData);
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
    void actualizeRealizedIdentifiers();
    void addRelationDataToModel(UMLRelationAnchor *source, UMLRelationAnchor *destination);

    UMLClassData *umlClassData;
    QList<UMLRelationAnchor *> anchors;
    QSet<QString> realizedIdentifiers;
    static constexpr int PADDING_HORIZONTAL = 12;
    static constexpr int PADDING_VERTICAL = 6;
    QFont TEXT_FONT = QFont(qApp->font().family(), 9, QFont::Normal);
    QFont CLASS_NAME_FONT = QFont(qApp->font().family(), 10, QFont::Bold);

    static constexpr qreal MIN_WIDTH = 60;
    static constexpr qreal ANCHOR_DRAG_OFFSET = 15;
    QColor HIGHLIGHT_COLOR = QColor(0, 90, 140);
    QColor TEXT_COLOR = Qt::black;
    QColor OUTLINE_COLOR = QColor(0, 130, 180);
    QColor SELECTED_OUTLINE_COLOR = QColor(25, 195, 235);
    QColor BACKGROUND_COLOR = Qt::white;
    QColor HEADER_BACKGROUND_COLOR = QColor(180, 220, 240);
};

#endif // UMLCLASS_H
