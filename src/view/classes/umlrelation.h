#ifndef UMLRELATION_H
#define UMLRELATION_H

#include <QGraphicsLineItem>
#include "model/umlrelationdata.h"
#include "umlrelationanchor.h"

class UMLClass;


class UMLRelation : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    UMLRelation(UMLRelationData* relation, UMLRelationAnchor* sourceAnchor, UMLRelationAnchor* destinationAnchor);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void remove();

private slots:
    void onAnchorRemoved(UMLRelationAnchor *anchor);

private:
    void setColorPen();
    void setCorrectPosition();

    const UMLRelationData* relation;
    const UMLRelationAnchor* sourceAnchor;
    const UMLRelationAnchor* destinationAnchor;
    static constexpr QColor LINE_COLOR = QColor(120, 135, 140);
};

#endif // UMLRELATION_H
