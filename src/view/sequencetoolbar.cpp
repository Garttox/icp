/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file sequencetoolbar.cpp
 * @author Michal Trlica (xtrlic02)
 */
#include "sequencetoolbar.h"

#include <view/sequence/newinstancedialog.h>
#include <view/sequence/umlcall.h>

SequenceToolBar::SequenceToolBar()
    :  QToolBar()
{
    createActions();
    setOrientation(Qt::Vertical);
    setStyleSheet("QToolButton { padding: 2px; margin: 2px; }");
    setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    addAction(addInstanceAction);
    addAction(removeSelectedAction);
}

void SequenceToolBar::changeView(SequenceDiagramView *view)
{
    this->view = view;
}

// - - - - - private - - - - -

QPoint SequenceToolBar::getViewportCenter()
{
    QRect rect(QPoint(), view->size());
    QPoint center = view->mapToScene(rect.center()).toPoint();
    return center;
}

void SequenceToolBar::createActions()
{
    addInstanceAction = new QAction(this);
    addInstanceAction->setIcon(QIcon("../res/addins.png"));
    addInstanceAction->setToolTip("Add instance (Ctrl+I)");
    addInstanceAction->setShortcut(QString("Ctrl+I"));
    connect(addInstanceAction, &QAction::triggered, this, &SequenceToolBar::addInstance);

    removeSelectedAction = new QAction(this);
    removeSelectedAction->setIcon(QIcon("../res/remove.png"));
    removeSelectedAction->setToolTip("Remove selected (Delete)");
    removeSelectedAction->setShortcut(Qt::Key_Delete);
    connect(removeSelectedAction, &QAction::triggered, this, &SequenceToolBar::removeSelected);
}

template<class T>
QList<T> SequenceToolBar::getSelectedOfGivenType()
{
    QList<T> filtered;
    foreach(QGraphicsItem *item, view->scene()->selectedItems())
    {
        if (T casted = dynamic_cast<T>(item))
        {
            filtered.append(casted);
        }
    }
    return filtered;
}

// - - - - - private slots - - - - -

void SequenceToolBar::addInstance()
{
    QPoint location = getViewportCenter();
    NewInstanceDialog *newInstanceDialog = new NewInstanceDialog(view->getUMLSequenceModel(), location.x());
    newInstanceDialog->show();
}

void SequenceToolBar::removeSelected()
{
    UMLSequenceModel *umlSequenceModel = view->getUMLSequenceModel();
    foreach(UMLCall *umlCall, getSelectedOfGivenType<UMLCall*>())
    {
        umlSequenceModel->removeCall(umlCall->getUMLCallModel());
    }
    foreach(UMLInstance *umlInstance, getSelectedOfGivenType<UMLInstance*>())
    {
        umlSequenceModel->removeInstance(umlInstance->getUMLInstanceModel());
    }
}
