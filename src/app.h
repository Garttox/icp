#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QGraphicsView>
#include "model\dataprovider.h"

class UMLData;

class App : public QMainWindow
{
    Q_OBJECT

public:
    App(QWidget *parent = 0);
private slots:
    void loadFile();
    void saveFile();
    void addClass();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QMenu *mainMenu;
    QToolBar *toolBar;
    QTabWidget *tabWidget;

    QAction *fileLoad;
    QAction *fileSave;
    QAction *addClassAction;

    void createActions();
    void createMainMenu();
    void createToolBar();
};

#endif // APP_H
