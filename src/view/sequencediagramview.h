#ifndef SEQUENCEDIAGRAMVIEW_H
#define SEQUENCEDIAGRAMVIEW_H

#include <QApplication>
#include <QGraphicsView>

#include <model/umlinstancemodel.h>
#include <model/umlsequencemodel.h>

class SequenceDiagramView : public QGraphicsView
{
    Q_OBJECT
public:
    SequenceDiagramView(QWidget* parent, UMLSequenceModel *umlSequenceModel);

    UMLSequenceModel *getUMLSequenceModel() const;
private slots:
    void onInstanceModelAdded(UMLInstanceModel *umlInstanceModel);
private:
    /**
     * @brief Draws the background of the view.
     */
    void drawBackgroundTiles();
    void addUMLInstance(UMLInstanceModel *umlInstanceModel);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    UMLSequenceModel *umlSequenceModel;
    int originX;
    int originY;
    static constexpr qreal TILE_SIZE = 60;
    QColor TILE_COLOR = QColor(225, 225, 225);
};

#endif // SEQUENCEDIAGRAMVIEW_H
