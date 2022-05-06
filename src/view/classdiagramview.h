/**
 * ICP - UML Application
 * @date 24/4/2022
 * @file classdiagramview.h
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#ifndef CLASSDIAGRAMVIEW_H
#define CLASSDIAGRAMVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWidget>
#include "classes/umlclass.h"
#include "model/umlclassmodel.h"
#include "model/umlmodel.h"

class ClassToolBar;

/**
 * @brief Extends QGraphicsView to implement specific functionalities for UML class diagram.
 * @authors Martin Bednář (xbedna77), Michal Trlica (xtrlic02)
 */
class ClassDiagramView : public QGraphicsView
{
    Q_OBJECT

public:
    ClassDiagramView(QWidget* parent);

    /**
     * @brief Create pixmap out of the current view, while hiding toolbar.
     * @return Pixel map of current viewport.
     */
    QPixmap getViewportPixmap();

    /**
     * @brief Adds new UMLClass, containing given UMLClassModel, to the scene.
     * @param umlClassModel Model to initialize with the UMLClass.
     */
    void addUMLClass(UMLClassModel *umlClassModel);

    void removeUMLClass(UMLClass *umlClass);
    void removeUMLClass(UMLClassModel *umlClassModel);

    /**
     * @brief Adds new UMLRelation, containing given UMLRelationModel, to the scene.
     * @param umlRelationModel Model to initialize with the UMLRelation.
     */
    void addUMLRelation(UMLRelationModel *umlRelationModel);

    void removeUMLRelation(UMLRelation *umlRelation);
    void removeUMLRelation(UMLRelationModel *umlRelationModel);

private slots:
    void onClassModelAdded(UMLClassModel *umlClassModel);
    void onClassModelRemoved(UMLClassModel *umlClassModel);
    void onRelationModelAdded(UMLRelationModel *umlRelationModel);
    void onRelationModelRemoved(UMLRelationModel *umlRelationModel);
    void onUmlModelCleared();

private:
    /**
     * @brief Gets UMLClass based on UMLClassModel given.
     * @param umlClassModel Model to search for in UMLClasses.
     * @return UMLClass corresponding to UMLClassModel, or nullptr when not found.
     */
    UMLClass *getUMLClass(UMLClassModel *umlClassModel);

    /**
     * @brief Gets UMLRelation based on UMLRelationModel given.
     * @param umlRelationModel Model to search for in UMLRelations.
     * @return UMLRelation corresponding to UMLRelationModel, or nullptr when not found.
     */
    UMLRelation *getUMLRelation(UMLRelationModel *umlRelationModel);

    /**
     * @brief Gets all the items of type T from the scene.
     * @return Scene's items of type T.
     */
    template <class T> QList<T> getItemsOfType();

    /**
     * @brief Removes all the relations connected to givem UMLClass.
     * @param umlClass UMLClass of which relations remove.
     */
    void removeRelationConnectedTo(UMLClass *umlClass);

    /**
     * @brief Draws the background of the view.
     */
    void drawBackgroundTiles();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    int originX;
    int originY;

    static constexpr qreal TILE_SIZE = 60;
    QColor TILE_COLOR = QColor(225, 225, 225);
};

#endif // CLASSDIAGRAMVIEW_H
