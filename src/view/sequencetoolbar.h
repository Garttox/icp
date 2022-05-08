#ifndef SEQUENCETOOLBAR_H
#define SEQUENCETOOLBAR_H

#include "sequencediagramview.h"

#include <QObject>
#include <QToolBar>

class SequenceToolBar : public QToolBar
{
    Q_OBJECT
public:
    SequenceToolBar();
    void changeView(SequenceDiagramView *view);
private:
    QPoint getViewportCenter();
    void createActions();

    SequenceDiagramView *view;
    QAction *addInstanceAction;
    QAction *removeSelectedAction;
    static constexpr qreal ICON_SIZE = 20;

private slots:
    void addInstance();
    void removeSelected();
};

#endif // SEQUENCETOOLBAR_H
