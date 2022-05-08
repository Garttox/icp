#include "umlinstance.h"
#include "umlcall.h"
#include "editinstancedialog.h"
#include <command/commandstack.h>
#include <command/sequence/moveinstancecommand.h>

#include <QColor>
#include <QFontMetricsF>
#include <QPainter>
#include <QPen>
#include <QGraphicsScene>


UMLInstance::UMLInstance(UMLInstanceModel *umlInstanceModel, UMLSequenceModel *umlSequenceModel)
    : umlInstanceModel(umlInstanceModel), umlSequenceModel(umlSequenceModel)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setPos(umlInstanceModel->getPosX(), 100);

    lifeLine = new UMLInstanceLifeLine(this);

    connect(umlSequenceModel, &UMLSequenceModel::instanceModelEdited, this, &UMLInstance::onUMLInstanceModelChanged);
}

QRectF UMLInstance::boundingRect() const
{
    return outlineRect();
}

QPointF UMLInstance::getStartCenter() const
{
    QRectF rect = outlineRect();
    QPointF startCenter = rect.center();
    startCenter.setY(rect.bottom());
    return startCenter;
}

QPointF UMLInstance::getEndCenter() const
{
    QPointF endCenter = getStartCenter();
    endCenter.setY(endCenter.y() + MAX_LENGTH);
    return endCenter;
}

qreal UMLInstance::getPosX() const
{
    return this->pos().x();
}

UMLSequenceModel *UMLInstance::getUMLSequenceModel() const
{
    return umlSequenceModel;
}

UMLInstanceModel *UMLInstance::getUMLInstanceModel() const
{
    return umlInstanceModel;
}

bool UMLInstance::correspondsTo(UMLInstanceModel *umlInstanceModel)
{
    return this->umlInstanceModel == umlInstanceModel;
}

int UMLInstance::getLifeLength()
{
    return calculateEndLifeLine() - calculateStartLifeLine();
}

// - - - - - protected - - - - -

void UMLInstance::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    int posX = this->pos().x();
    CommandStack::getInstance().push(new MoveInstanceCommand(umlInstanceModel, posX));
    QGraphicsItem::mouseReleaseEvent(event);
}

void UMLInstance::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    EditInstanceDialog *editInstanceDialog = new EditInstanceDialog(umlInstanceModel);
    editInstanceDialog->exec();
}

void UMLInstance::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */* widget */)
{
    QPen pen = QPen(isSelected() ? SELECTED_OUTLINE_COLOR : OUTLINE_COLOR);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(BACKGROUND_COLOR);
    QRectF rect = outlineRect();
    painter->drawRect(rect);
    painter->setPen(TEXT_COLOR);
    painter->setFont(TEXT_FONT);
    painter->drawText(rect, Qt::AlignCenter, umlInstanceModel->getDisplayName());
}

QVariant UMLInstance::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            setZValue(isSelected() ? 1 : 0);
            lifeLine->setZValue(-1);
            break;
        case QGraphicsItem::ItemPositionHasChanged:
            if (this->pos().x() < -boundingRect().left())
            {
                setPos(-boundingRect().left(), this->posY);
            }
            else
            {
                setPos(this->pos().x(), this->posY);
            }
            break;
        default:
            break;  // Keeps Qt Creator without warnings
    }
    return QGraphicsItem::itemChange(change, value);
}

// - - - - - private slots - - - - -

void UMLInstance::onUMLInstanceModelChanged(UMLInstanceModel *umlInstanceModel)
{
    if (correspondsTo(umlInstanceModel))
    {
        setPos(umlInstanceModel->getPosX(), pos().y());
    }
    update();
}

// - - - - - private - - - - -

QRectF UMLInstance::outlineRect() const
{

    QFontMetricsF fontMetrics(TEXT_FONT);
    QRectF rect = fontMetrics.boundingRect(umlInstanceModel->getDisplayName());
    rect.adjust(-PADDING, -PADDING, +PADDING, +PADDING);
    rect.translate(-rect.center());
    return rect;
}

int UMLInstance::calculateStartLifeLine()
{
    UMLCallModel *umlCallModel = umlSequenceModel->instanceCreatedBy(umlInstanceModel);
    if (umlCallModel)
    {
        // TODO:
    }
    else
    {
        return getStartCenter().y();
    }
}

int UMLInstance::calculateEndLifeLine()
{
    UMLCallModel *umlCallModel = umlSequenceModel->instanceDestroyedBy(umlInstanceModel);
    if (umlCallModel)
    {
        // TODO:
    }
    else
    {
        return getStartCenter().y() + MAX_LENGTH;
    }
}
