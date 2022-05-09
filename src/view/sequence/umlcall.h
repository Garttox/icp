/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlcall.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef UMLCALL_H
#define UMLCALL_H

#include "umlcallarrow.h"

#include <QGraphicsItem>
#include <QObject>

#include <model/umlcallmodel.h>

class UMLInstance;
/**
 * @brief Graphical object for displaying UML Call.
 * @author Michal Trlica (xtrlic02)
 */
class UMLCall : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    UMLCall(UMLCallModel *umlCallModel, UMLInstance *sourceInstance, UMLInstance *destinationInstance);
    QRectF boundingRect() const override;
    qreal getSourceDistance();
    UMLCallModel *getUMLCallModel() const;

    /**
     * @brief Checks if given UMLCallModel are being displayed by this object.
     * @param umlCallModel UMLCallModel to check.
     * @return True, if UMLCall is displaying given UMLCallModel.
     */
    bool correspondsTo(UMLCallModel *umlCallModel);
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private slots:
    void onCallModelChange(UMLCallModel *umlCallModel);
private:
    QRectF outlineRect() const;
    void setCorrectPosition();
    /**
     * @brief Calculates height of UML Call from UMLCallModel duration attribute
     * @return qreal Height of UML Call
     */
    qreal getDuration() const;
    /**
     * @brief Calculates Y position from UMLCallModel atTime attribute
     * @return qreal Y position relative to UML instance
     */
    qreal getAtTime() const;
    void setupArrows();

    UMLCallModel *umlCallModel;
    UMLInstance *sourceInstance;
    UMLInstance *destinationInstance;
    UMLCallArrow *forwardArrow;
    UMLCallArrow *returnArrow;

    static constexpr qreal MESSAGE_WIDTH = 20;
    static constexpr int DEFAULT_POSX_EXTERN = 50;
    QColor OUTLINE_COLOR = QColor(0, 130, 180);
    QColor SELECTED_OUTLINE_COLOR = QColor(25, 195, 235);
    QColor BACKGROUND_COLOR = QColor(235, 240, 250);
};

#endif // UMLCALL_H
