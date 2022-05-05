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
#include "model/umlclassdata.h"
#include "model/umldata.h"

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
     * @brief Adds new UMLClass, containing given UMLClassData, to the scene.
     * @param classData Data to initialize with the UMLClass.
     */
    void addUMLClass(UMLClassData *umlClassData);

    void removeUMLClass(UMLClass *umlClass);
    void removeUMLClass(UMLClassData *umlClassData);

    /**
     * @brief Adds new UMLRelation, containing given UMLRelationData, to the scene.
     * @param relationData Data to initialize with the UMLRelation.
     */
    void addUMLRelation(UMLRelationData *relationData);

    void removeUMLRelation(UMLRelation *umlRelation);
    void removeUMLRelation(UMLRelationData *umlRelationData);

private slots:
    void onClassModelAdded(UMLClassData *umlClassData);
    void onClassModelRemoved(UMLClassData *umlClassData);
    void onRelationModelAdded(UMLRelationData *umlRelationData);
    void onRelationModelRemoved(UMLRelationData *umlRelationData);
    void onUmlModelCleared();

private:
    /**
     * @brief Gets UMLClass based on UMLClassData given.
     * @param umlClassData Data to search for in UMLClasses.
     * @return UMLClass corresponding to UMLClassData, or nullptr when not found.
     */
    UMLClass *getUMLClass(UMLClassData *umlClassData);

    /**
     * @brief Gets UMLRelation based on UMLRelationData given.
     * @param umlRelationData Data to search for in UMLRelations.
     * @return UMLRelation corresponding to UMLRelationData, or nullptr when not found.
     */
    UMLRelation *getUMLRelation(UMLRelationData *umlRelationData);

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
