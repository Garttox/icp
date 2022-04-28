#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QGraphicsView>
#include "model\dataprovider.h"
#include "model\umldata.h"

class App : public QMainWindow
{
    Q_OBJECT

public:
    App(QWidget *parent = 0);

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QMenu *mainMenu;
    QToolBar *toolBar;
    QTabWidget *tabWidget;

    QAction *fileLoad;
    QAction *fileSave;
    QAction *addClassAction;
    QAction *removeSelectedAction;

    void createActions();
    void createMainMenu();
    void createToolBar();
    void removeSelectedRelations();
    void removeSelectedClasses();

    template <class T>
    QList<T> getSelectedOfGivenType();

    static constexpr qreal SCENE_SIZE = 3000;

private slots:
    void loadFile();
    void saveFile();
    void addClass();
    void removeSelected();

};

#endif // APP_H
