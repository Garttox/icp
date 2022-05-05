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

private slots:
    /**
     * @brief Called, when UMLClassData model is added.
     * @param classData Newly added UML class data.
     */
    void classModelAdded(UMLClassData *classData);

    /**
     * @brief Called, when UMLRelationData model is added.
     * @param relationData Newly added UML relation data.
     */
    void relationModelAdded(UMLRelationData *relationData);

    /**
     * @brief Called, when all data has been cleared from UMLData model.
     */
    void umlModelCleared();

private:
    /**
     * @brief Gets UMLClass based on UMLClassData given.
     * @param umlClassData Data to search for in UMLClasses.
     * @return UMLClass corresponding to UMLClassData, or nullptr when not found.
     */
    UMLClass *getUMLClass(UMLClassData *umlClassData);

    /**
     * @brief Draws the background of the view.
     */
    void drawBackgroundTiles();

    /**
     * @brief Adds new UMLClass, containing given UMLClassData, to the scene.
     * @param classData Data to initialize with the UMLClass.
     */
    void addUMLClass(UMLClassData *classData);

    /**
     * @brief Adds new UMLRelation, containing given UMLRelationData, to the scene.
     * @param relationData Data to initialize with the UMLRelation.
     */
    void addUMLRelation(UMLRelationData *relationData);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    int originX;
    int originY;

    static constexpr qreal TILE_SIZE = 60;
    QColor TILE_COLOR = QColor(225, 225, 225);
};

#endif // CLASSDIAGRAMVIEW_H
