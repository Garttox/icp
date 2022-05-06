#ifndef UMLCALL_H
#define UMLCALL_H

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

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    QRectF outlineRect() const;
    void setCorrectPosition();
    UMLCallModel *umlCallModel;
    UMLInstance *sourceInstance;
    UMLInstance *destinationInstance;

    QColor OUTLINE_COLOR = QColor(0, 130, 180);
    QColor SELECTED_OUTLINE_COLOR = QColor(25, 195, 235);
    QColor BACKGROUND_COLOR = QColor(140, 140, 140);
};

#endif // UMLCALL_H
