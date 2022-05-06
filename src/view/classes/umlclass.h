/**
 * ICP - UML Application
 * @date 24/4/2022
 * @file umlclass.h
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#ifndef UMLCLASS_H
#define UMLCLASS_H

#include <QApplication>
#include <QColor>
#include <QGraphicsItem>
#include <QSet>
#include <QEvent>
#include <QVariant>
#include "model/umlmodel.h"
#include "model/umlclassmodel.h"
#include "umlrelationanchor.h"
#include "umlrelation.h"

/**
 * @brief Graphical object for displaying UML classes and their anchors.
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */
class UMLClass : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    UMLClass(UMLClassModel *umlClassModel);
    QRectF boundingRect() const override;
    
    /**
     * @brief Checks if given UMLClassModel are being displayed by this object.
     * @param umlClassModel UMLClassModel to check.
     * @return True, if UMLClass is displaying given UMLClassModel. 
     */
    bool correspondsTo(UMLClassModel *umlClassModel);

    /**
     * @brief Get the anchor, specified by id, of the class. 
     * @param id Id to search for.
     * @return UMLRelationAnchor if found, nullptr otherwise.
     */
    UMLRelationAnchor *getAnchorById(int id) const;

    /**
     * @brief Get underlying UMLClassModel.
     * @return Underlying UMLClassModel.
     */
    UMLClassModel *getUMLClassModel() const;
    
    /**
     * @brief Get id of given relation anchor.
     * @param anchor Anchor to search for.
     * @return Id of the given anchor if found, -1 otherwise.
     */
    int getAnchorId(UMLRelationAnchor *anchor);

private slots:
    void onClassModelEdited(UMLClassModel* umlClassModel);
    void onRelationModelAdded(UMLRelationModel *umlRelationModel);
    void onRelationModelEdited(UMLRelationModel *umlRelationModel);
    void onRelationModelRemoved(UMLRelationModel *umlRelationModel);
    void onAnchorDragged(UMLRelationAnchor *anchor, QPointF endpoint);
    void onAnchorDragReleased(UMLRelationAnchor *source, UMLRelationAnchor *destination);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QRectF outlineRect() const;
    qreal maxTextWidth() const;
    void addRelationAnchors();
    void resetAnchorsPositions();
    void setAnchorsVisible(bool enabled);
    void actualizeRealizedIdentifiers();
    void addRelationToModel(UMLRelationAnchor *source, UMLRelationAnchor *destination);

    UMLClassModel *umlClassModel;
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
