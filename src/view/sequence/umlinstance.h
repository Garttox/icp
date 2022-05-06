#ifndef UMLINSTANCE_H
#define UMLINSTANCE_H

#include <QGraphicsItem>
#include <QApplication>
#include <QColor>
#include <QFont>

#include <model/umlinstancemodel.h>

class UMLInstance : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    UMLInstance(UMLInstanceModel *umlInstanceModel);
    QRectF boundingRect() const override;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private:
    QRectF outlineRect() const;
    UMLInstanceModel *umlInstanceModel;

    qreal posY = DEFAULT_POSY;

    static constexpr qreal DEFAULT_POSY = 100;
    static constexpr int PADDING = 8;
    QFont NAME_FONT = QFont(qApp->font().family(), 10, QFont::Bold);
    QColor TEXT_COLOR = Qt::black;
    QColor OUTLINE_COLOR = QColor(0, 130, 180);
    QColor SELECTED_OUTLINE_COLOR = QColor(25, 195, 235);
    QColor BACKGROUND_COLOR = Qt::white;
};

#endif // UMLINSTANCE_H
