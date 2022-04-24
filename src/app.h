#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QGraphicsView>

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

    QAction *fileLoad;
    QAction *fileSave;
    QAction *addClassAction;

    UMLData *umlData;

    void createActions();
    void createMainMenu();
    void createToolBar();
};

#endif // APP_H
