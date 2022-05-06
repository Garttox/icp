#ifndef UMLINSTANCE_H
#define UMLINSTANCE_H

#include "umlinstancelifeline.h"

#include <QGraphicsItem>
#include <QApplication>
#include <QColor>
#include <QFont>

#include <model/umlsequencemodel.h>
#include <model/umlinstancemodel.h>

class UMLInstance : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    UMLInstance(UMLInstanceModel *umlInstanceModel, UMLSequenceModel *umlSequenceModel);
    QRectF boundingRect() const override;
    QPointF getStartCenter() const;
    QPointF getEndCenter() const;
    qreal getPosX() const;
    /**
     * @brief Checks if given UMLInstanceModel are being displayed by this object.
     * @param umlInstanceModel UMLInstanceModel to check.
     * @return True, if UMLInstance is displaying given UMLInstanceModel.
     */
    bool correspondsTo(UMLInstanceModel *umlInstanceModel);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private:
    QRectF outlineRect() const;
    int getLifeLength();
    int calculateStartLifeLine();
    int calculateEndLifeLine();
    UMLInstanceModel *umlInstanceModel;
    UMLSequenceModel *umlSequenceModel;
    UMLInstanceLifeLine *lifeLine;

    qreal posY = DEFAULT_POSY;
    static constexpr int MAX_LENGTH = 1000;
    static constexpr qreal DEFAULT_POSY = 20;
    static constexpr int PADDING = 8;
    QFont TEXT_FONT = QFont(qApp->font().family(), 10, QFont::Bold);
    QColor TEXT_COLOR = Qt::black;
    QColor OUTLINE_COLOR = QColor(0, 130, 180);
    QColor SELECTED_OUTLINE_COLOR = QColor(25, 195, 235);
    QColor BACKGROUND_COLOR = Qt::white;
};

#endif // UMLINSTANCE_H
