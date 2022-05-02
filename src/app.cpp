/**
 * ICP - UML Application
 * @date 22/4/2022
 * @file app.cpp
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#include <QFileDialog>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

#include "app.h"
#include "model/umldata.h"
#include "model/dataprovider.h"

App::App(QWidget *parent) :
    QMainWindow(parent)
{
    UMLData* umlData = new UMLData();
    DataProvider::getInstance().setUMLData(umlData);

    setWindowTitle(tr("UML App"));
    tabWidget = new QTabWidget(this);
    view = new ClassDiagramView(this);
    scene = new QGraphicsScene(view);
    scene->setSceneRect(0, 0, SCENE_SIZE, SCENE_SIZE);
    view->setMinimumSize(600, 600);
    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);

    classToolBar = new ClassToolBar(view, scene);
    addToolBar(classToolBar);
    tabWidget->addTab(view, QString("Class Diagram"));
    tabWidget->addTab(new QWidget(), QString("Sequence 1"));
    setCentralWidget(tabWidget);

    createActions();
    createMainMenu();
}

//  - - - - - private  - - - - -

void App::createActions()
{
    fileLoad = new QAction("Load", this);
    fileLoad->setShortcut(QString("Ctrl+L"));
    connect(fileLoad, SIGNAL(triggered()), this, SLOT(loadFile()));

    fileSave = new QAction("Save", this);
    fileSave->setShortcut(QString("Ctrl+S"));
    connect(fileSave, SIGNAL(triggered()), this, SLOT(saveFile()));

    imageExport = new QAction("Export", this);
    imageExport->setShortcut(QString("Ctrl+E"));
    connect(imageExport, SIGNAL(triggered()), this, SLOT(exportImage()));
}

void App::createMainMenu()
{
    mainMenu = menuBar()->addMenu("File");
    mainMenu->addAction(fileLoad);
    mainMenu->addAction(fileSave);
    mainMenu->addAction(imageExport);
}

void App::displayErrorMessageBox(QString title, QString message)
{
    QMessageBox messageBox;
    messageBox.critical(nullptr, title, message);
    messageBox.setFixedSize(500, 200);
}

// - - - - - private slots - - - - -

void App::loadFile()
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", DEFAULT_PATH, "JSON (*.json)");
    qInfo() << fileName;
    if (fileName.length() == 0)
    {
        return; // User closed the dialog
    }
    umlData->clearData();
    QJsonDocument doc;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        displayErrorMessageBox("Reading error", "Error occured while reading the file");
        return;
    }
    QByteArray byteFile = file.readAll();
    doc = QJsonDocument::fromJson(byteFile);
    QJsonObject json = doc.object();

    // validate if file is in json format
    if (doc.isNull())
    {
        displayErrorMessageBox("Loading error", "Given file data are not in supported format.");
        return;
    }

    bool loadedSuccesfully = umlData->loadData(json);

    if (!loadedSuccesfully)
    {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "Loading error", "Given file data are probably corrupted.");
        messageBox.setFixedSize(500, 200);
        return;
    }

}

void App::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", DEFAULT_PATH, "JSON (*.json)");
    if (fileName.length() == 0)
    {
        return; // User closed the dialog
    }

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
    {
        displayErrorMessageBox("Save error", "Error occured while saving the file.");
        return;
    }

    QJsonDocument document;
    QJsonObject root = DataProvider::getInstance().getUMLData()->getSaveData();
    document.setObject(root);
    file.write(document.toJson());
    file.close();
}



void App::exportImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export image", DEFAULT_PATH, "PNG (*.png)");
    if (fileName.length() == 0)
    {
        return; // User closed the dialog
    }

    QPixmap pixmap = view->getViewportPixmap();
    if (!pixmap.save(fileName))
    {
        displayErrorMessageBox("Export error", "Error occured while exporting to the file.");
        return;
    }
}
