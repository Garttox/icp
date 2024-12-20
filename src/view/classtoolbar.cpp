/**
 * ICP - UML Application
 * @date 29/4/2022
 * @file classtoolbar.cpp
 * @author Martin Bednář (xbedna77)
 */

#include <QIcon>
#include <QAction>
#include <QDebug>
#include <view/sequence/newinstancedialog.h>
#include <model/modelprovider.h>
#include "classtoolbar.h"
#include "classes/newclassdialog.h"
#include "ui_newclassdialog.h"

ClassToolBar::ClassToolBar(ClassDiagramView *view, QGraphicsScene *scene) :
    QToolBar("Tools", view), view(view), scene(scene)
{
    createActions();
    setOrientation(Qt::Vertical);
    setStyleSheet("QToolButton { padding: 2px; margin: 2px; }");
    setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    addAction(addClassAction);
    addAction(addInterfaceAction);
    addAction(removeSelectedAction);
}

// - - - - - private - - - - -

void ClassToolBar::createActions()
{
    addClassAction = new QAction(this);
    addClassAction->setIcon(QIcon("../res/add.png"));
    addClassAction->setToolTip("Add class (Ctrl+N)");
    addClassAction->setShortcut(QString("Ctrl+N"));
    connect(addClassAction, &QAction::triggered, this, &ClassToolBar::addClass);

    addInterfaceAction = new QAction(this);
    addInterfaceAction->setIcon(QIcon("../res/addi.png"));
    addInterfaceAction->setToolTip("Add interface (Ctrl+M)");
    addInterfaceAction->setShortcut(QString("Ctrl+M"));
    connect(addInterfaceAction, &QAction::triggered, this, &ClassToolBar::addInterface);

    removeSelectedAction = new QAction(this);
    removeSelectedAction->setIcon(QIcon("../res/remove.png"));
    removeSelectedAction->setToolTip("Remove selected (Delete)");
    removeSelectedAction->setShortcut(Qt::Key_Delete);
    connect(removeSelectedAction, &QAction::triggered, this, &ClassToolBar::removeSelected);
}

QPoint ClassToolBar::getViewportCenter()
{
    QRect rect(QPoint(), view->size());
    QPoint center = view->mapToScene(rect.center()).toPoint();
    return center;
}

template<class T>
QList<T> ClassToolBar::getSelectedOfGivenType()
{
    QList<T> filtered;
    foreach(QGraphicsItem *item, scene->selectedItems())
    {
        if (T casted = dynamic_cast<T>(item))
        {
            filtered.append(casted);
        }
    }
    return filtered;
}


// - - - - - private slots - - - - -

void ClassToolBar::addClass()
{
    QPoint position = getViewportCenter();
    NewClassDialog *newClassDialog = new NewClassDialog(UMLClassType::CLASS, position);
    newClassDialog->show();
}

void ClassToolBar::addInterface()
{
    QPoint position = getViewportCenter();
    NewClassDialog *newClassDialog = new NewClassDialog(UMLClassType::INTERFACE, position);
    newClassDialog->show();
}

void ClassToolBar::removeSelected()
{
    foreach(UMLRelation *umlRelation, getSelectedOfGivenType<UMLRelation*>())
    {
        ModelProvider::getInstance().getModel()->removeRelation(umlRelation->getUMLRelationModel());
    }
    foreach(UMLClass *umlClass, getSelectedOfGivenType<UMLClass*>())
    {
        ModelProvider::getInstance().getModel()->removeClass(umlClass->getUMLClassModel());
    }
}
