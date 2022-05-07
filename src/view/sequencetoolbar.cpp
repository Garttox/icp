#include "sequencetoolbar.h"

SequenceToolBar::SequenceToolBar(SequenceDiagramView *view, QGraphicsScene *scene)
    :  QToolBar("sequence", view), view(view), scene(scene)
{

}
