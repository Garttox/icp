#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QGraphicsView>
#include "view/classdiagramview.h"
#include "view/classtoolbar.h"

class App : public QMainWindow
{
    Q_OBJECT

public:
    App(QWidget *parent = 0);

private:
    QGraphicsScene *scene;
    ClassDiagramView *view;
    QMenu *mainMenu;
    QTabWidget *tabWidget;
    ClassToolBar *classToolBar;

    QAction *fileLoad;
    QAction *fileSave;

    void createActions();
    void createMainMenu();

    static constexpr qreal SCENE_SIZE = 2400;

private slots:
    void loadFile();
    void saveFile();

};

#endif // APP_H
