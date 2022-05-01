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

    QAction *fileLoad;
    QAction *fileSave;
    QAction *imageExport;

    void createActions();
    void createMainMenu();
    void displayErrorMessageBox(QString title, QString message);

    const QString DEFAULT_PATH = "../examples";
    static constexpr qreal SCENE_SIZE = 2400;

private slots:
    void loadFile();
    void saveFile();
    void exportImage();

};

#endif // APP_H
