#include "umlcall.h"
#include "umlinstance.h"

#include <QPainter>
#include <QPen>
#include <QRectF>

UMLCall::UMLCall(UMLCallModel *umlCallModel, UMLInstance *sourceInstance, UMLInstance *destinationInstance)
    : QObject(), QGraphicsItem(destinationInstance), umlCallModel(umlCallModel),
      sourceInstance(sourceInstance), destinationInstance(destinationInstance)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setCorrectPosition();
    setPos(pos().x(), getAtTime());

    setupArrows();
}

QRectF UMLCall::boundingRect() const
{
    return outlineRect();
}

qreal UMLCall::getSourceDistance()
{
    if (this->sourceInstance)
    {
        return this->sourceInstance->getPosX() - this->destinationInstance->getPosX();
    }
    return DEFAULT_POSX_EXTERN - this->destinationInstance->getPosX();
}

UMLCallModel *UMLCall::getUMLCallModel() const
{
    return umlCallModel;
}

// - - - - - protected - - - - -

void UMLCall::paint(QPainter *painter, const QStyleOptionGraphicsItem */* option */, QWidget */* widget */)
{
    setCorrectPosition();

    QPen pen = QPen(isSelected() ? SELECTED_OUTLINE_COLOR : OUTLINE_COLOR);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(BACKGROUND_COLOR);
    QRectF rect = outlineRect();

    if (umlCallModel->getType() == UMLCallType::MESSAGE)
    {
        painter->drawRect(rect);
    }
    else if (umlCallModel->getType() == UMLCallType::DESTROY)
    {
        painter->drawLine(rect.topLeft(), rect.bottomRight());
        painter->drawLine(rect.topRight(), rect.bottomLeft());
    }
}

QVariant UMLCall::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            setZValue(isSelected() ? 1 : 0);
            break;
        case QGraphicsItem::ItemPositionHasChanged:
            setCorrectPosition();
            break;
        default:
            break;  // Keeps Qt Creator without warnings
    }
    return QGraphicsItem::itemChange(change, value);
}

// - - - - - private - - - - -

QRectF UMLCall::outlineRect() const
{
    QRectF rect = QRectF(0,0,MESSAGE_WIDTH, getDuration());
    rect.translate(-rect.center());
    return rect;
}

void UMLCall::setCorrectPosition()
{
    if (this->pos().y() + this->boundingRect().top() < destinationInstance->getStartCenter().y())
    {
        setPos(0, destinationInstance->getStartCenter().y() - this->boundingRect().top());
    }
    else if (this->pos().y() + this->boundingRect().bottom() > destinationInstance->getEndCenter().y())
    {
        setPos(0, destinationInstance->getEndCenter().y() - this->boundingRect().bottom());
    }
    else
    {
        setPos(0, this->pos().y());
    }
}

qreal UMLCall::getDuration() const
{
    return ((qreal)destinationInstance->getLifeLength() / UMLCallModel::RELATIVE_MAX_LIFE) * (qreal)umlCallModel->getDuration();
}

qreal UMLCall::getAtTime() const
{
    return ((qreal)destinationInstance->getLifeLength() / UMLCallModel::RELATIVE_MAX_LIFE) * (qreal)umlCallModel->getAtTime();
}

void UMLCall::setupArrows()
{
    forwardArrow = new UMLCallArrow(this, UMLCallArrowType::CALL_MESSAGE);
    returnArrow = new UMLCallArrow(this, UMLCallArrowType::RETURN_MESSAGE);

    if (umlCallModel->getAsync())
    {
        returnArrow->setVisible(false);
    }
}
