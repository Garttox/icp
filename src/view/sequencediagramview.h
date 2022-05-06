#ifndef SEQUENCEDIAGRAMVIEW_H
#define SEQUENCEDIAGRAMVIEW_H

#include <QApplication>
#include <QGraphicsView>

#include <model/umlinstancedata.h>
#include <model/umlsequencedata.h>

#include <view/sequence/umlinstance.h>

class SequenceDiagramView : public QGraphicsView
{
    Q_OBJECT
public:
    SequenceDiagramView(QWidget* parent, UMLSequenceData *umlSequenceData);

    UMLSequenceData *getUMLSequenceData() const;
private slots:
    void onInstanceModelAdded(UMLInstanceData *umlInstanceData);
    void onCallModelAdded(UMLCallData *umlCallData);
private:
    /**
     * @brief Draws the background of the view.
     */
    void drawBackgroundTiles();
    void addUMLInstance(UMLInstanceData *umlInstanceData);
    void addUMLCall(UMLCallData *umlCallData);

    UMLInstance *getUMLInstance(UMLInstanceData *umlInstanceData);

    /**
     * @brief Gets all the items of type T from the scene.
     * @return Scene's items of type T.
     */
    template <class T> QList<T> getItemsOfType();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    UMLSequenceData *umlSequenceData;
    int originX;
    int originY;
    static constexpr qreal TILE_SIZE = 60;
    QColor TILE_COLOR = QColor(225, 225, 225);
};

#endif // SEQUENCEDIAGRAMVIEW_H
