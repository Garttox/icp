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
#include "model\umldata.h"
#include "model\dataprovider.h"

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
    // setCentralWidget(view);

    tabWidget->addTab(view, QString("Class Diagram"));
    tabWidget->addTab(new QWidget(), QString("Sequence 1"));
    setCentralWidget(tabWidget);

    createActions();
    createMainMenu();
}

//  - - - - - private  - - - - -

void App::createActions()
{
    fileLoad = new QAction(tr("&Load"), this);
    fileLoad->setShortcut(tr("Ctrl+L"));
    connect(fileLoad, SIGNAL(triggered()), this, SLOT(loadFile()));

    fileSave = new QAction(tr("&Save"), this);
    fileSave->setShortcut(QString("Ctrl+S"));
    connect(fileSave, SIGNAL(triggered()), this, SLOT(saveFile()));
}

void App::createMainMenu()
{
    mainMenu = menuBar()->addMenu(tr("&File"));
    mainMenu->addAction(fileLoad);
    mainMenu->addAction(fileSave);
}

// - - - - - private slots - - - - -

void App::loadFile()
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", "../examples");
    qInfo() << fileName;
    if (fileName.length() == 0)
    {
        return; // user closed dialog
    }
    umlData->clearData();
    QJsonDocument doc;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "failed to read the file";
        QMessageBox messageBox;
        messageBox.critical(0,"Reading error","Error occured while reading the file");
        messageBox.setFixedSize(500, 200);
        return;
    }
    QByteArray byteFile = file.readAll();
    doc = QJsonDocument::fromJson(byteFile);
    QJsonObject json = doc.object();

    // validate if file is in json format
    if (doc.isNull())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Loading error","Given file data are not in supported format.");
        messageBox.setFixedSize(500, 200);
        return;
    }

    bool loadedSuccesfully = umlData->loadData(json);

    if (!loadedSuccesfully)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Loading error","Given file data are probably corrupted.");
        messageBox.setFixedSize(500, 200);
        return;
    }

}

void App::saveFile()
{
    // TODO: saving to file
}
