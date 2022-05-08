#include "umlcall.h"
#include "umlinstance.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>
#include <QRectF>

#include <command/commandstack.h>
#include <command/sequence/movecallcommand.h>

UMLCall::UMLCall(UMLCallModel *umlCallModel, UMLInstance *sourceInstance, UMLInstance *destinationInstance)
    : QObject(), QGraphicsItem(destinationInstance), umlCallModel(umlCallModel),
      sourceInstance(sourceInstance), destinationInstance(destinationInstance)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setPos(0, getAtTime());
    setupArrows();

    connect(umlCallModel, &UMLCallModel::modelChanged, this, &UMLCall::onCallModelChange);
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

bool UMLCall::correspondsTo(UMLCallModel *umlCallModel)
{
    return this->umlCallModel == umlCallModel;
}

// - - - - - protected - - - - -
void UMLCall::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    int atTime;
    if (umlCallModel->getType() == UMLCallType::DESTROY)
    {
        if (sourceInstance)
        {
            atTime = pos().y() * (UMLCallModel::RELATIVE_MAX_LIFE / (qreal)sourceInstance->getLifeLength());
        }
        else
        {
            atTime = pos().y() * (UMLCallModel::RELATIVE_MAX_LIFE / (qreal)UMLInstance::getMaxLifeLength());
        }
    }
    else
    {
        atTime = pos().y() * (UMLCallModel::RELATIVE_MAX_LIFE / (qreal)destinationInstance->getLifeLength());
    }
    CommandStack::getInstance().push(new MoveCallCommand(umlCallModel, atTime));
    QGraphicsItem::mouseReleaseEvent(event);
}

void UMLCall::paint(QPainter *painter, const QStyleOptionGraphicsItem */* option */, QWidget */* widget */)
{
    setCorrectPosition();

    QPen pen = QPen(isSelected() ? SELECTED_OUTLINE_COLOR : OUTLINE_COLOR);
    pen.setWidth(2);
    painter->setPen(pen);
    QRectF rect = outlineRect();

    if (umlCallModel->getType() == UMLCallType::MESSAGE)
    {
        painter->setBrush(BACKGROUND_COLOR);
        painter->drawRect(rect);
    }
    else if (umlCallModel->getType() == UMLCallType::CREATE)
    {
        painter->setBrush(Qt::white);
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

// - - - - - private slots - - - - -

void UMLCall::onCallModelChange(UMLCallModel */*umlCallModel*/)
{
    setPos(0, getAtTime());
    update();
}

// - - - - - private - - - - -

QRectF UMLCall::outlineRect() const
{
    QRectF rect;
    if (umlCallModel->getType() == UMLCallType::DESTROY || umlCallModel->getType() == UMLCallType::CREATE)
    {
        rect = QRectF(0,0,MESSAGE_WIDTH, MESSAGE_WIDTH);
    }
    else
    {
        rect = QRectF(0,0,MESSAGE_WIDTH, getDuration());
    }
    rect.translate(-rect.center());
    return rect;
}

void UMLCall::setCorrectPosition()
{
    if (umlCallModel->getType() == UMLCallType::DESTROY)
    {
        if (pos().y() < destinationInstance->sceneBoundingRect().bottom() + boundingRect().top())
        {
            setPos(0, destinationInstance->sceneBoundingRect().bottom() + boundingRect().top());
        }
        else if (pos().y() > destinationInstance->sceneBoundingRect().bottom() + UMLInstance::getMaxLifeLength() + boundingRect().top())
        {
            setPos(0, destinationInstance->sceneBoundingRect().bottom() + UMLInstance::getMaxLifeLength() + boundingRect().top());
        }
        else
        {
            setPos(0, pos().y());
        }
    }
    else if (umlCallModel->getType() == UMLCallType::CREATE)
    {
        setPos(0, destinationInstance->boundingRect().bottom() + boundingRect().height());
    }
    else
    {
        if (pos().y() > destinationInstance->getEndCenter().y() - boundingRect().bottom() - destinationInstance->getStartCenter().y())
        {
            setPos(0, destinationInstance->getEndCenter().y() - boundingRect().bottom() - destinationInstance->getStartCenter().y());
        }
        else if (pos().y() < boundingRect().bottom() + destinationInstance->boundingRect().bottom())
        {
            setPos(0, boundingRect().bottom() + destinationInstance->boundingRect().bottom());
        }
        else {
            setPos(0, this->pos().y());
        }
    }
}

qreal UMLCall::getDuration() const
{
    return ((qreal)destinationInstance->getLifeLength() / UMLCallModel::RELATIVE_MAX_LIFE) * (qreal)umlCallModel->getDuration();
}

qreal UMLCall::getAtTime() const
{
    UMLCallType type = umlCallModel->getType();
    if (type == UMLCallType::DESTROY || type == UMLCallType::CREATE)
    {
        if (sourceInstance)
        {
            return ((qreal)sourceInstance->getLifeLength() / UMLCallModel::RELATIVE_MAX_LIFE) * (qreal)umlCallModel->getAtTime();
        }
        return ((qreal)UMLInstance::getMaxLifeLength() / UMLCallModel::RELATIVE_MAX_LIFE) * (qreal)umlCallModel->getAtTime();
    }

    return ((qreal)destinationInstance->getLifeLength() / UMLCallModel::RELATIVE_MAX_LIFE) * (qreal)umlCallModel->getAtTime();
}

void UMLCall::setupArrows()
{
    UMLCallType type = umlCallModel->getType();
    if (type == UMLCallType::MESSAGE)
    {
        forwardArrow = new UMLCallArrow(this, UMLCallArrowType::CALL_MESSAGE);
        returnArrow = new UMLCallArrow(this, UMLCallArrowType::RETURN_MESSAGE);

        if (umlCallModel->getAsync())
        {
            returnArrow->setVisible(false);
        }
    }
    else if (type == UMLCallType::DESTROY)
    {
        forwardArrow = new UMLCallArrow(this, UMLCallArrowType::DESTROY);
    }
    else
    {
        forwardArrow = new UMLCallArrow(this, UMLCallArrowType::CREATE);
    }
}
