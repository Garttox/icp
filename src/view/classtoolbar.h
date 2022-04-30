#ifndef CLASSTOOLBAR_H
#define CLASSTOOLBAR_H

#include <QToolBar>
#include "view/classtoolbar.h"
#include "view/classdiagramview.h"


class ClassToolBar : public QToolBar
{
    Q_OBJECT
public:
    ClassToolBar(ClassDiagramView *view, const QGraphicsScene *scene);
private:
    void createActions();
    QPoint getViewportCenter();
    template <class T> QList<T> getSelectedOfGivenType();

    QAction *addClassAction;
    QAction *addInterfaceAction;
    QAction *removeSelectedAction;
    QAction *undoAction;
    const ClassDiagramView *view;
    const QGraphicsScene *scene;



private slots:
    void addClass();
    void addInterface();
    void removeSelected();
    void undo();

};

#endif // CLASSTOOLBAR_H
