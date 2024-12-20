/**
 * ICP - UML Application
 * @date 24/4/2022
 * @file umlclass.cpp
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#include <QtGui>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <algorithm>
#include <QGraphicsView>
#include <QDebug>
#include "command/commandstack.h"
#include "command/classes/addrelationcommand.h"
#include "command/classes/moveclasscommand.h"
#include "model/modelprovider.h"
#include "umlclass.h"
#include "editclassdialog.h"
#include "ui_editclassdialog.h"
#include "umlrelationanchor.h"
#include "umlclassnotifier.h"

UMLClass::UMLClass(UMLClassModel *umlClassModel) :
    QObject(),
    QGraphicsItem(),
    umlClassModel(umlClassModel)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setPos(umlClassModel->getPosX(), umlClassModel->getPosY());
    addRelationAnchors();

    // connect signals
    UMLModel *umlModel = ModelProvider::getInstance().getModel();
    UMLClassNotifier* notifier = UMLClassNotifier::getInstance();

    connect(notifier, &UMLClassNotifier::anchorDragged, this, &UMLClass::onAnchorDragged);
    connect(notifier, &UMLClassNotifier::anchorDragReleased, this, &UMLClass::onAnchorDragReleased);
    connect(umlModel, &UMLModel::classModelEdited, this, &UMLClass::onClassModelEdited);
    connect(umlModel, &UMLModel::relationModelAdded, this, &UMLClass::onRelationModelAdded);
    connect(umlModel, &UMLModel::relationModelEdited, this, &UMLClass::onRelationModelEdited);
    connect(umlModel, &UMLModel::relationModelRemoved, this, &UMLClass::onRelationModelRemoved);
}

QRectF UMLClass::boundingRect() const
{
    return outlineRect();
}

bool UMLClass::correspondsTo(UMLClassModel *umlClassModel)
{
    return this->umlClassModel == umlClassModel;
}

UMLRelationAnchor *UMLClass::getAnchorById(int id) const
{
    return (id >= 0 && id < anchors.count()) ? anchors.at(id) : nullptr;
}

UMLClassModel *UMLClass::getUMLClassModel() const
{
    return umlClassModel;
}

int UMLClass::getAnchorId(UMLRelationAnchor *anchor)
{
    return anchors.indexOf(anchor);
}

// - - - - - private slots  - - - - -

void UMLClass::onClassModelEdited(UMLClassModel *umlClassModel)
{
    if (correspondsTo(umlClassModel))
    {
        setPos(umlClassModel->getPosX(), umlClassModel->getPosY());
        resetAnchorsPositions();
    }
    actualizeRealizedIdentifiers();
    update();
}

void UMLClass::onRelationModelAdded(UMLRelationModel *umlRelationModel)
{
    if (umlRelationModel->getType() == UMLRelationType::GENERALISATION)
    {
        actualizeRealizedIdentifiers();
        update();
    }
}

void UMLClass::onRelationModelEdited(UMLRelationModel * /*umlRelationModel*/)
{
    actualizeRealizedIdentifiers();
    update();
}

void UMLClass::onRelationModelRemoved(UMLRelationModel *umlRelationModel)
{
    if (umlRelationModel->getType() == UMLRelationType::GENERALISATION)
    {
        actualizeRealizedIdentifiers();
        update();
    }
}

void UMLClass::onAnchorDragged(UMLRelationAnchor *anchor, QPointF endpoint)
{
    if (!anchors.contains(anchor))
    {
        QRectF bounds = sceneBoundingRect();
        QRectF adjusted = bounds.adjusted(-ANCHOR_DRAG_OFFSET, -ANCHOR_DRAG_OFFSET, ANCHOR_DRAG_OFFSET, ANCHOR_DRAG_OFFSET);
        setAnchorsVisible(adjusted.contains(endpoint));
    }
}

void UMLClass::onAnchorDragReleased(UMLRelationAnchor *source, UMLRelationAnchor *destination)
{
    if (destination != nullptr && anchors.contains(source))
    {
        addRelationToModel(source, destination);
    }
    setAnchorsVisible(isSelected());
}

// - - - - - protected  - - - - -

void UMLClass::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/)
{
    EditClassDialog *editClassDialog = new EditClassDialog(umlClassModel);
    editClassDialog->exec();
    resetAnchorsPositions();
}

void UMLClass::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint position = this->pos().toPoint();
    CommandStack::getInstance().push(new MoveClassCommand(umlClassModel, position));
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant UMLClass::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            setZValue(isSelected() ? 1 : 0);
            setAnchorsVisible(isSelected());
            break;
        default:
            break;  // Keeps Qt Creator without warnings
    }
    return QGraphicsItem::itemChange(change, value);
}

void UMLClass::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    QPen pen = QPen(isSelected() ? SELECTED_OUTLINE_COLOR : OUTLINE_COLOR);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(BACKGROUND_COLOR);
    QRectF rect = outlineRect();
    painter->drawRect(rect);
    painter->setPen(TEXT_COLOR);

    QFontMetricsF textFontMetrics(TEXT_FONT);
    QFontMetricsF classNameFontMetrics(CLASS_NAME_FONT);

    QList<UMLFieldModel *> fields = umlClassModel->getFields();
    QList<UMLMethodModel *> methods = umlClassModel->getMethods();

    QPointF point = rect.topLeft();
    point.setX(point.x() + PADDING_HORIZONTAL);
    point.setY(point.y() + classNameFontMetrics.height());

    // class table background
    QRectF headerRect(rect.topLeft(), QPointF(rect.topLeft().x() + rect.width(), rect.topLeft().y() + classNameFontMetrics.height()+ PADDING_VERTICAL));
    headerRect.adjust(1, 1, -1, -1);
    painter->fillRect(headerRect, HEADER_BACKGROUND_COLOR);

    // class name
    painter->setFont(CLASS_NAME_FONT);
    painter->drawText(point, umlClassModel->getDisplayName());

    point.setY(point.y() + PADDING_VERTICAL);

    painter->drawLine(point.x() - PADDING_HORIZONTAL, point.y(), point.x() - PADDING_HORIZONTAL + rect.width(), point.y());

    painter->setFont(TEXT_FONT);
    // fields
    foreach(auto *field, fields)
    {
        QString string = field->toString();
        QColor color = realizedIdentifiers.contains(string) ? HIGHLIGHT_COLOR : TEXT_COLOR;
        painter->setPen(color);
        point.setY(point.y() + textFontMetrics.height());
        painter->drawText(point, string);
    }
    // separator
    if (!methods.empty() && !fields.empty()) {
        point.setY(point.y() + 4);
        painter->drawLine(point.x() - PADDING_HORIZONTAL, point.y(), point.x() - PADDING_HORIZONTAL + rect.width(), point.y());
    }
    // methods
    foreach(auto *method, methods)
    {
        QString string = method->toString();
        QColor color = realizedIdentifiers.contains(string) ? HIGHLIGHT_COLOR : TEXT_COLOR;
        painter->setPen(color);
        point.setY(point.y() + textFontMetrics.height());
        painter->drawText(point, string);
    }
}

// - - - - - private - - - - -

QRectF UMLClass::outlineRect() const
{
    const int separatorsHeight = 8;
    QFontMetricsF textFontMetrics(TEXT_FONT);
    QFontMetricsF classNameFontMetrics(CLASS_NAME_FONT);
    QList<UMLFieldModel *> fields = umlClassModel->getFields();
    QList<UMLMethodModel *> methods = umlClassModel->getMethods();
    QRectF rect = QRectF(0, 0, maxTextWidth(), textFontMetrics.height() * (fields.size() + methods.size()) + classNameFontMetrics.height() + separatorsHeight);
    rect.adjust(-PADDING_HORIZONTAL, -PADDING_VERTICAL, +PADDING_HORIZONTAL, +PADDING_VERTICAL);
    rect.translate(-rect.center());
    return rect;
}

qreal UMLClass::maxTextWidth() const
{
    QFontMetricsF textFontMetrics(TEXT_FONT);
    QFontMetricsF classNameFontMetrics(CLASS_NAME_FONT);
    QList<UMLFieldModel *> fields = umlClassModel->getFields();
    QList<UMLMethodModel *> methods = umlClassModel->getMethods();
    qreal maxWidth = std::max(classNameFontMetrics.width(umlClassModel->getDisplayName()), MIN_WIDTH);

    foreach(auto *method, methods)
    {
        qreal rowWidth = textFontMetrics.width(method->toString());
        maxWidth = std::max(rowWidth, maxWidth);
    }

    foreach(auto *field, fields)
    {
        qreal rowWidth = textFontMetrics.width(field->toString());
        maxWidth = std::max(rowWidth, maxWidth);
    }
    return maxWidth;
}

void UMLClass::addRelationAnchors()
{
    for (int i = -1; i <= 1; i++)
    {
        qreal rel = 0.6 * i;
        anchors.append(new UMLRelationAnchor(this, rel, +1));
        anchors.append(new UMLRelationAnchor(this, rel, -1));
        anchors.append(new UMLRelationAnchor(this, +1, rel));
        anchors.append(new UMLRelationAnchor(this, -1, rel));
    }
}

void UMLClass::resetAnchorsPositions()
{
    foreach (UMLRelationAnchor *anchor, anchors)
    {
        anchor->setPositionRelativeToParent();
    }
}

void UMLClass::setAnchorsVisible(bool enabled)
{
    foreach (UMLRelationAnchor *anchor, anchors)
    {
        anchor->setVisible(enabled);
    }
}

void UMLClass::actualizeRealizedIdentifiers()
{
    realizedIdentifiers.clear();
    QSet<UMLRelationModel *> relations = ModelProvider::getInstance().getModel()->getRelationsWithSourceClass(umlClassModel);
    QSet<UMLAttribute *> ownIdentifiers = umlClassModel->getIdentifiers();
    foreach (UMLRelationModel *relation, relations)
    {
        if (relation->getType() == UMLRelationType::GENERALISATION)
        {
            foreach (UMLAttribute *identifier, ownIdentifiers)
            {
                QString signature = identifier->toString();
                if (relation->getDestination()->haveIdentifierWithSignature(signature))
                {
                    realizedIdentifiers.insert(signature);
                }
            }
        }
    }
}

void UMLClass::addRelationToModel(UMLRelationAnchor *source, UMLRelationAnchor *destination)
{
    int srcAnchorId = source->getId();
    int destAnchorId = destination->getId();
    UMLClassModel *sourceClassModel = source->getParentUMLClass()->getUMLClassModel();
    UMLClassModel *destinationClassModel = destination->getParentUMLClass()->getUMLClassModel();
    UMLRelationType type = UMLRelationType::ASSOCIATION;
    UMLRelationModel *umlRelationModel = new UMLRelationModel(sourceClassModel, destinationClassModel, type, srcAnchorId, destAnchorId);
    CommandStack::getInstance().push(new AddRelationCommand(umlRelationModel));
}

