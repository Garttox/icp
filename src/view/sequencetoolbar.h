#ifndef SEQUENCETOOLBAR_H
#define SEQUENCETOOLBAR_H

#include "sequencediagramview.h"

#include <QObject>
#include <QToolBar>

class SequenceToolBar : public QToolBar
{
    Q_OBJECT
public:
    SequenceToolBar(SequenceDiagramView *view, QGraphicsScene *scene);
private:
    SequenceDiagramView *view;
    QGraphicsScene *scene;
};

#endif // SEQUENCETOOLBAR_H
