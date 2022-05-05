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
#include "model/dataprovider.h"
#include "umlclass.h"
#include "editclassdialog.h"
#include "ui_editclassdialog.h"
#include "umlrelationanchor.h"
#include "umlclassnotifier.h"

UMLClass::UMLClass(UMLClassData *umlClassData) :
    QObject(),
    umlClassData(umlClassData)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setPos(umlClassData->getPosX(), umlClassData->getPosY());
    addRelationAnchors();

    // connect signals
    connect(UMLClassNotifier::getInstance(), SIGNAL(anchorDragged(UMLRelationAnchor*,QPointF)),
            this, SLOT(onAnchorDragged(UMLRelationAnchor*,QPointF)));
    connect(UMLClassNotifier::getInstance(), SIGNAL(anchorDragReleased(UMLRelationAnchor*,UMLRelationAnchor*)),
            this, SLOT(onAnchorDragReleased(UMLRelationAnchor*,UMLRelationAnchor*)));
    connect(DataProvider::getInstance().getUMLData(), SIGNAL(classModelEdited(UMLClassData*)),
            this, SLOT(onClassModelEdited(UMLClassData*)));
    connect(DataProvider::getInstance().getUMLData(), SIGNAL(relationModelAdded(UMLRelationData*)),
            this, SLOT(onRelationModelAdded(UMLRelationData*)));
    connect(DataProvider::getInstance().getUMLData(), SIGNAL(relationModelEdited(UMLRelationData*)),
            this, SLOT(onRelationModelEdited(UMLRelationData*)));
    connect(DataProvider::getInstance().getUMLData(), SIGNAL(relationModelRemoved(UMLRelationData*)),
            this, SLOT(onRelationModelRemoved(UMLRelationData*)));

}

QRectF UMLClass::boundingRect() const
{
    return outlineRect();
}

bool UMLClass::correspondsTo(UMLClassData *umlClassData)
{
    return this->umlClassData == umlClassData;
}

UMLRelationAnchor *UMLClass::getAnchorById(int id) const
{
    return (id >= 0 && id < anchors.count()) ? anchors.at(id) : nullptr;
}

UMLClassData *UMLClass::getUMLClassData() const
{
    return umlClassData;
}

int UMLClass::getAnchorId(UMLRelationAnchor *anchor)
{
    return anchors.indexOf(anchor);
}

void UMLClass::remove()
{
    emit UMLClassNotifier::getInstance()->classRemoved(this);
    scene()->removeItem(this);
    anchors.clear();
    DataProvider::getInstance().getUMLData()->removeClass(umlClassData);
    delete this;
}

// - - - - - private slots  - - - - -

void UMLClass::onClassModelEdited(UMLClassData */*umlClassData*/)
{
    actualizeRealizedIdentifiers();
    update();
}

void UMLClass::onRelationModelAdded(UMLRelationData *relationData)
{
    if (relationData->getType() == UMLRelationType::GENERALISATION)
    {
        actualizeRealizedIdentifiers();
        update();
    }
}

void UMLClass::onRelationModelEdited(UMLRelationData * /*relationData*/)
{
    actualizeRealizedIdentifiers();
    update();
}

void UMLClass::onRelationModelRemoved(UMLRelationData *relationData)
{
    if (relationData->getType() == UMLRelationType::GENERALISATION)
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
        addRelationDataToModel(source, destination);
    }
    setAnchorsVisible(isSelected());
}

// - - - - - protected  - - - - -

void UMLClass::mouseDoubleClickEvent(QGraphicsSceneMouseEvent */*event*/)
{
    EditClassDialog *editClassDialog = new EditClassDialog(umlClassData);
    editClassDialog->exec();
    resetAnchorsPositions();
}

QVariant UMLClass::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            setZValue(isSelected() ? 1 : 0);
            setAnchorsVisible(isSelected());
            break;
        case QGraphicsItem::ItemPositionHasChanged:
            umlClassData->setPosX(this->pos().x());
            umlClassData->setPosY(this->pos().y());
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

    QList<UMLFieldData *> fields = umlClassData->getFields();
    QList<UMLMethodData *> methods = umlClassData->getMethods();

    QPointF point = rect.topLeft();
    point.setX(point.x() + PADDING_HORIZONTAL);
    point.setY(point.y() + classNameFontMetrics.height());

    // class table background
    QRectF headerRect(rect.topLeft(), QPointF(rect.topLeft().x() + rect.width(), rect.topLeft().y() + classNameFontMetrics.height()+ PADDING_VERTICAL));
    headerRect.adjust(1, 1, -1, -1);
    painter->fillRect(headerRect, HEADER_BACKGROUND_COLOR);

    // class name
    painter->setFont(CLASS_NAME_FONT);
    painter->drawText(point, umlClassData->getDisplayName());

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
    QList<UMLFieldData *> fields = umlClassData->getFields();
    QList<UMLMethodData *> methods = umlClassData->getMethods();
    QRectF rect = QRectF(0, 0, maxTextWidth(), textFontMetrics.height() * (fields.size() + methods.size()) + classNameFontMetrics.height() + separatorsHeight);
    rect.adjust(-PADDING_HORIZONTAL, -PADDING_VERTICAL, +PADDING_HORIZONTAL, +PADDING_VERTICAL);
    rect.translate(-rect.center());
    return rect;
}

qreal UMLClass::maxTextWidth() const
{
    QFontMetricsF textFontMetrics(TEXT_FONT);
    QFontMetricsF classNameFontMetrics(CLASS_NAME_FONT);
    QList<UMLFieldData *> fields = umlClassData->getFields();
    QList<UMLMethodData *> methods = umlClassData->getMethods();
    qreal maxWidth = std::max(classNameFontMetrics.width(umlClassData->getDisplayName()), MIN_WIDTH);

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
    QSet<UMLRelationData *> relations = DataProvider::getInstance().getUMLData()->getRelationsWithSourceClass(umlClassData);
    QSet<UMLAttribute *> ownIdentifiers = umlClassData->getIdentifiers();
    foreach (UMLRelationData *relation, relations)
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

void UMLClass::addRelationDataToModel(UMLRelationAnchor *source, UMLRelationAnchor *destination)
{
    int srcAnchorId = source->getId();
    int destAnchorId = destination->getId();
    UMLClassData *srcClassData = source->getParentUMLClass()->getUMLClassData();
    UMLClassData *destClassData = destination->getParentUMLClass()->getUMLClassData();
    UMLRelationType type = UMLRelationType::ASSOCIATION;
    UMLRelationData *relationData = new UMLRelationData(srcClassData, destClassData, type, srcAnchorId, destAnchorId);
    DataProvider::getInstance().getUMLData()->addRelation(relationData);
}

