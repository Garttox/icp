/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file sequencediagramview.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef SEQUENCEDIAGRAMVIEW_H
#define SEQUENCEDIAGRAMVIEW_H

#include <QApplication>
#include <QGraphicsView>

#include <model/umlinstancemodel.h>
#include <model/umlsequencemodel.h>

#include <view/sequence/umlcall.h>
#include <view/sequence/umlinstance.h>

/**
 * @brief Extends QGraphicsView to implement specific functionalities for UML sequence diagram.
 * @authors Michal Trlica (xtrlic02)
 */
class SequenceDiagramView : public QGraphicsView
{
    Q_OBJECT
public:
    SequenceDiagramView(QWidget* parent, UMLSequenceModel *umlSequenceModel);

    /**
     * @brief Checks if given UMLSequenceModel are being displayed by this object.
     * @param umlSequenceModel UMLSequenceModel to check.
     * @return True, if SequenceDiagramView is displaying given UMLSequenceModel.
     */
    bool correspondsTo(UMLSequenceModel *umlSequenceModel);

    UMLSequenceModel *getUMLSequenceModel() const;

    /**
     * @brief Generates all components from UMLSequenceModel
     */
    void loadSequence();

private slots:
    void onInstanceModelAdded(UMLInstanceModel *umlInstanceModel);
    void onInstanceModelRemoved(UMLInstanceModel *umlInstanceModel);
    void onCallModelAdded(UMLCallModel *umlCallModel);
    void onCallModelRemoved(UMLCallModel *umlCallModel);

private:
    /**
     * @brief Draws the background of the view.
     */
    void drawBackgroundTiles();
    void addUMLInstance(UMLInstanceModel *umlInstanceModel);
    void addUMLCall(UMLCallModel *umlCallModel);
    void removeUMLInstance(UMLInstanceModel *umlInstanceModel);
    void removeUMLCall(UMLCallModel *umlCallModel);
    UMLInstance *getUMLInstance(UMLInstanceModel *umlInstanceModel);
    UMLCall *getUMLCall(UMLCallModel *umlCallModel);
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
