#include <QtGui>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <algorithm>
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
    textColor = Qt::black;
    outlineColor = QColor(0, 130, 180);
    selectedOutlineColor = QColor(25, 195, 235);
    backgroundColor = Qt::white;
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setPos(umlClassData->getPosX(), umlClassData->getPosY());
    addRelationAnchors();

    // connect signals
    connect(UMLClassNotifier::getInstance(), SIGNAL(anchorDragged(UMLRelationAnchor*,QPointF)),
            this, SLOT(onAnchorDragged(UMLRelationAnchor*,QPointF)));
    connect(UMLClassNotifier::getInstance(), SIGNAL(anchorDragReleased(UMLRelationAnchor*,UMLRelationAnchor*)),
            this, SLOT(onAnchorDragReleased(UMLRelationAnchor*,UMLRelationAnchor*)));
    connect(DataProvider::getInstance().getUMLData(), SIGNAL(relationModelAdded(UMLRelationData*)),
            this, SLOT(onRelationModelAdded(UMLRelationData*)));
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

void UMLClass::onRelationModelAdded(UMLRelationData *relationData)
{
    UMLClassData *source = relationData->getSource();
    UMLClassData *destination = relationData->getDestination();
    if (relationData->getType() == UMLRelationType::GENERALISATION && source == umlClassData)
    {
        foreach (UMLIdentifier *identifier, umlClassData->getIdentifiers())
        {
            QString signature = identifier->toString();
            if (destination->haveIdentifierWithSignature(signature))
            {
                realizedIdentifiers.append(signature);
            }
        }
    }
    update();
}

void UMLClass::onRelationModelRemoved(UMLRelationData *relationData)
{
    UMLClassData *source = relationData->getSource();
    UMLClassData *destination = relationData->getDestination();
    if (relationData->getType() == UMLRelationType::GENERALISATION && source == umlClassData)
    {
        foreach (UMLIdentifier *identifier, umlClassData->getIdentifiers())
        {
            QString signature = identifier->toString();
            if (destination->haveIdentifierWithSignature(signature))
            {
                realizedIdentifiers.removeOne(signature);
            }
        }
    }
    update();
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
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        setZValue(isSelected() ? 1 : 0);
        setAnchorsVisible(isSelected());
    }
    return QGraphicsItem::itemChange(change, value);
}

void UMLClass::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    QPen pen = QPen(isSelected() ? selectedOutlineColor : outlineColor);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(backgroundColor);
    QRectF rect = outlineRect();
    painter->drawRect(rect);
    painter->setPen(textColor);

    QFontMetricsF metrics{qApp->font()};
    //painter->drawText(rect, Qt::AlignCenter, umlClassData->getName());
    QList<UMLFieldData *> fields = umlClassData->getFields();
    QList<UMLMethodData *> methods = umlClassData->getMethods();
    QPointF point = rect.topLeft();
    qreal offsetX = 6.0;
    point.setY(point.y() + metrics.height());
    point.setX(point.x() + offsetX);

    // class name
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(point, umlClassData->getDisplayName());
    font.setBold(false);
    painter->setFont(font);
    point.setY(point.y() + metrics.height() / 2);
    point.setX(point.x() - offsetX);
    painter->drawLine(point, QPointF(point.x() + rect.width(), point.y()));
    point.setX(point.x() + offsetX);
    point.setY(point.y() + metrics.height());

    // fields
    foreach(auto *field, fields)
    {
        QString string = field->toString();
        QColor color = realizedIdentifiers.contains(string) ? HIGHLIGHT_COLOR : Qt::black;
        painter->setPen(color);
        painter->drawText(point, string);
        point.setY(point.y() + metrics.height());
    }

    // separator
    point.setX(point.x() - offsetX);
    point.setY(point.y() - metrics.height()/2);
    painter->drawLine(point, QPointF(point.x() + rect.width(), point.y()));
    point.setX(point.x() + offsetX);
    point.setY(point.y() + metrics.height());

    // methods
    foreach(auto *method, methods)
    {
        QString string = method->toString();
        QColor color = realizedIdentifiers.contains(string) ? HIGHLIGHT_COLOR : Qt::black;
        painter->setPen(color);
        painter->drawText(point, string);
        point.setY(point.y() + metrics.height());
    }
}

// - - - - - private - - - - -

QRectF UMLClass::outlineRect() const
{
    const int padding = 12;
    QFontMetricsF metrics{ qApp->font() };
    QList<UMLFieldData *> fields = umlClassData->getFields();
    QList<UMLMethodData *> methods = umlClassData->getMethods();
    QRectF rect = QRectF(0, 0, maxTextWidth() + padding, metrics.height() * (fields.size() + methods.size()) + padding);
    rect.adjust(-padding, -padding, +padding, +padding);
    rect.translate(-rect.center());
    return rect;
}


qreal UMLClass::maxTextWidth() const
{
    QFontMetricsF metrics{qApp->font()};
    QList<UMLFieldData *> fields = umlClassData->getFields();
    QList<UMLMethodData *> methods = umlClassData->getMethods();
    qreal maxWidth = std::max(metrics.width(umlClassData->getDisplayName()), MIN_WIDTH);

    foreach(auto *method, methods)
    {
        qreal rowWidth = metrics.width(method->toString());
        maxWidth = std::max(rowWidth, maxWidth);
    }

    foreach(auto *field, fields)
    {
        qreal rowWidth = metrics.width(field->toString());
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

