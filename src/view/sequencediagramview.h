#ifndef SEQUENCEDIAGRAMVIEW_H
#define SEQUENCEDIAGRAMVIEW_H

#include <QApplication>
#include <QGraphicsView>

#include <model/umlinstancedata.h>
#include <model/umlsequencedata.h>

class SequenceDiagramView : public QGraphicsView
{
    Q_OBJECT
public:
    SequenceDiagramView(QWidget* parent, UMLSequenceData *umlSequenceData);

    void addInstance(UMLInstanceData *umlInstanceData) const;
    UMLSequenceData *getUMLSequenceData() const;
private slots:

private:
    /**
     * @brief Draws the background of the view.
     */
    void drawBackgroundTiles();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    UMLSequenceData *umlSequenceData;
    int originX;
    int originY;
    static constexpr qreal TILE_SIZE = 60;
    QColor TILE_COLOR = QColor(225, 225, 225);
};

#endif // SEQUENCEDIAGRAMVIEW_H
