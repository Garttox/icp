/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file sequencetoolbar.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef SEQUENCETOOLBAR_H
#define SEQUENCETOOLBAR_H

#include "sequencediagramview.h"

#include <QObject>
#include <QToolBar>

/**
 * @brief Class extending QToolBar and adding specific actions to it.
 * @author Michal Trlica (xtrlic02)
 */
class SequenceToolBar : public QToolBar
{
    Q_OBJECT
public:
    SequenceToolBar();
    /**
     * @brief Changes active view on which actions responds.
     * @param view SequenceDiagramView that  to be active. 
     */
    void changeView(SequenceDiagramView *view);
private:
    QPoint getViewportCenter();
    void createActions();
    /**
     * @brief Gets all the items of type T, that are selected in scene.
     * @return Scene's selected items of type T.
     */
    template <class T> QList<T> getSelectedOfGivenType();
    SequenceDiagramView *view;
    QAction *addInstanceAction;
    QAction *removeSelectedAction;
    static constexpr qreal ICON_SIZE = 20;

private slots:
    void addInstance();
    void removeSelected();
};

#endif // SEQUENCETOOLBAR_H
