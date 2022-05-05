#ifndef UMLINSTANCE_H
#define UMLINSTANCE_H

#include <QGraphicsItem>
#include <QApplication>
#include <QColor>
#include <QFont>

#include <model/umlinstancedata.h>

class UMLInstance : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    UMLInstance(UMLInstanceData *umlInstanceData);
    QRectF boundingRect() const override;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    QRectF outlineRect() const;
    UMLInstanceData *umlInstanceData;

    static constexpr int PADDING = 8;
    QFont NAME_FONT = QFont(qApp->font().family(), 10, QFont::Bold);
    QColor TEXT_COLOR = Qt::black;
    QColor OUTLINE_COLOR = QColor(0, 130, 180);
    QColor SELECTED_OUTLINE_COLOR = QColor(25, 195, 235);
    QColor BACKGROUND_COLOR = Qt::white;
};

#endif // UMLINSTANCE_H
