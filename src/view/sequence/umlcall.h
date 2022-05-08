#ifndef UMLCALL_H
#define UMLCALL_H

#include "umlcallarrow.h"

#include <QGraphicsItem>
#include <QObject>

#include <model/umlcallmodel.h>

class UMLInstance;

class UMLCall : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    UMLCall(UMLCallModel *umlCallModel, UMLInstance *sourceInstance, UMLInstance *destinationInstance);
    QRectF boundingRect() const override;
    qreal getSourceDistance();
    UMLCallModel *getUMLCallModel() const;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    QRectF outlineRect() const;
    void setCorrectPosition();
    qreal getDuration() const;
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
    QColor BACKGROUND_COLOR = QColor(140, 140, 140);
};

#endif // UMLCALL_H
