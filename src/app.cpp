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

// - - - - - private slots - - - - -

void App::loadFile()
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", "../examples");
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
        qWarning() << "failed to read the file";
        QMessageBox messageBox;
        messageBox.critical(nullptr, "Reading error", "Error occured while reading the file");
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
        messageBox.critical(nullptr, "Loading error", "Given file data are not in supported format.");
        messageBox.setFixedSize(500, 200);
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
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "../examples");
    if (fileName.length() == 0)
    {
        return; // User closed the dialog
    }

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "Save error", "Error occured while saving the file.");
        messageBox.setFixedSize(500, 200);
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
    QString fileName = QFileDialog::getSaveFileName(this, "Export image", "../examples");
    if (fileName.length() == 0)
    {
        return; // User closed the dialog
    }

    classToolBar->setVisible(false);
    QPixmap pixmap = view->grab(view->sceneRect().toRect());
    QRect crop(0, 0, view->width(), view->height());
    classToolBar->setVisible(true);

    if (!pixmap.copy(crop).save(fileName))
    {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "Export error", "Error occured while exporting to the file.");
        messageBox.setFixedSize(500, 200);
        return;
    }
}
