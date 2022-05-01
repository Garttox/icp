#ifndef CLASSTOOLBAR_H
#define CLASSTOOLBAR_H

#include <QToolBar>
#include "view/classtoolbar.h"
#include "view/classdiagramview.h"


/**
 * @brief Class extending QToolBar and adding specific actions to it.
 * @author Martin Bednář (xbedna77)
 */
class ClassToolBar : public QToolBar
{
    Q_OBJECT
public:
    ClassToolBar(ClassDiagramView *view, const QGraphicsScene *scene);

private:
    /**
     * @brief Creates QActions and adds them.
     */
    void createActions();

    /**
     * @brief Gets center of the view's viewport.
     * @return View's viewport center.
     */
    QPoint getViewportCenter();

    /**
     * @brief Gets all the items of type T, that are selected in scene.
     * @return Scene's selected items of type T.
     */
    template <class T> QList<T> getSelectedOfGivenType();

    QAction *addClassAction;
    QAction *addInterfaceAction;
    QAction *removeSelectedAction;
    QAction *undoAction;
    const ClassDiagramView *view;
    const QGraphicsScene *scene;
    static constexpr qreal ICON_SIZE = 20;

private slots:
    void addClass();
    void addInterface();
    void removeSelected();
    void undo();

};

#endif // CLASSTOOLBAR_H
