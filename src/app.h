/**
 * ICP - UML Application
 * @date 22/4/2022
 * @file app.h
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

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
    QAction *imageExport;
    QAction *addSequenceTab;

    void createActions();
    void createMainMenu();
    void displayErrorMessageBox(QString title, QString message);

    const QString DEFAULT_PATH = "../examples";
    static constexpr qreal SCENE_SIZE = 2400;

private slots:
    void loadFile();
    void saveFile();
    void exportImage();
    void addSequenceDiagram(UMLSequenceData *umlSequenceData);
    void removeSequenceDiagram(int tabIndex);
    void addSequenceDiagramDialog();

};

#endif // APP_H
