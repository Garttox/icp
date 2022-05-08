/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlinstance.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef UMLINSTANCE_H
#define UMLINSTANCE_H

#include "umlinstancelifeline.h"

#include <QGraphicsItem>
#include <QApplication>
#include <QColor>
#include <QFont>

#include <model/umlsequencemodel.h>
#include <model/umlinstancemodel.h>

/**
 * @brief Graphical object for displaying UML Instance.
 */
class UMLInstance : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    UMLInstance(UMLInstanceModel *umlInstanceModel, UMLSequenceModel *umlSequenceModel);
    QRectF boundingRect() const override;
    QPointF getStartCenter() const;
    QPointF getEndCenter();
    qreal getPosX() const;
    UMLSequenceModel *getUMLSequenceModel() const;
    UMLInstanceModel *getUMLInstanceModel() const;
    /**
     * @brief Checks if given UMLInstanceModel are being displayed by this object.
     * @param umlInstanceModel UMLInstanceModel to check.
     * @return True, if UMLInstance is displaying given UMLInstanceModel.
     */
    bool correspondsTo(UMLInstanceModel *umlInstanceModel);
    /**
     * @brief Calculates length of UML Lifeline.
     * @return Lenght in pixel of UML Lifeline.
     */
    int getLifeLength();
    static int getMaxLifeLength();
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private slots:
    void onUMLInstanceModelChanged(UMLInstanceModel *umlInstanceModel);
private:
    QRectF outlineRect() const;
    int calculateStartLifeLine();
    int calculateEndLifeLine();
    void setCorrectPosition();
    UMLInstanceModel *umlInstanceModel;
    UMLSequenceModel *umlSequenceModel;
    UMLInstanceLifeLine *lifeLine;

    qreal posY = 50;
    static constexpr int MAX_LENGTH = 900;
    static constexpr qreal DEFAULT_POSY = 50;
    static constexpr int PADDING = 8;
    QFont TEXT_FONT = QFont(qApp->font().family(), 10, QFont::Bold);
    QColor TEXT_COLOR = Qt::black;
    QColor OUTLINE_COLOR = QColor(0, 130, 180);
    QColor SELECTED_OUTLINE_COLOR = QColor(25, 195, 235);
    QColor BACKGROUND_COLOR = Qt::white;
};

#endif // UMLINSTANCE_H
