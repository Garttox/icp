#ifndef SEQUENCEDIAGRAMVIEW_H
#define SEQUENCEDIAGRAMVIEW_H

#include <QApplication>
#include <QGraphicsView>

#include <model/umlinstancemodel.h>
#include <model/umlsequencemodel.h>

#include <view/sequence/umlinstance.h>

class SequenceDiagramView : public QGraphicsView
{
    Q_OBJECT
public:
    SequenceDiagramView(QWidget* parent, UMLSequenceModel *umlSequenceModel);

    UMLSequenceModel *getUMLSequenceModel() const;
private slots:
    void onInstanceModelAdded(UMLInstanceModel *umlInstanceModel);
    void onCallModelAdded(UMLCallModel *umlCallModel);
private:
    /**
     * @brief Draws the background of the view.
     */
    void drawBackgroundTiles();
    void addUMLInstance(UMLInstanceModel *umlInstanceModel);
    void addUMLCall(UMLCallModel *umlCallModel);

    UMLInstance *getUMLInstance(UMLInstanceModel *umlInstanceModel);

    /**
     * @brief Gets all the items of type T from the scene.
     * @return Scene's items of type T.
     */
    template <class T> QList<T> getItemsOfType();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    UMLSequenceModel *umlSequenceModel;
    int originX;
    int originY;
    static constexpr qreal TILE_SIZE = 60;
    QColor TILE_COLOR = QColor(225, 225, 225);
};

#endif // SEQUENCEDIAGRAMVIEW_H
