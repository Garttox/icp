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
#include <QTabBar>
#include <QToolButton>

#include <view/sequencediagramview.h>
#include <view/sequence/newsequencedialog.h>

#include "app.h"
#include "data/umldata.h"
#include "model/umlmodel.h"
#include "model/modelprovider.h"
#include "command/commandstack.h"

App::App(QWidget *parent) :
    QMainWindow(parent)
{
    UMLModel* umlModel = new UMLModel();
    ModelProvider::getInstance().setModel(umlModel);

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

    createActions();
    createMainMenu();

    classToolBar = new ClassToolBar(view, scene);
    addToolBar(classToolBar);
    tabWidget->addTab(view, QString("Class Diagram"));
    tabWidget->setTabsClosable(true);
    tabWidget->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);
    QToolButton *addTabButton = new QToolButton();
    addTabButton->setDefaultAction(addSequenceTab);
    tabWidget->setCornerWidget(addTabButton, Qt::TopRightCorner);
    setCentralWidget(tabWidget);

    connect(tabWidget, &QTabWidget::tabCloseRequested,this, &App::removeSequenceDiagram);
    connect(umlModel, &UMLModel::sequenceModelAdded, this, &App::addSequenceDiagram);
}

//  - - - - - private  - - - - -

void App::createActions()
{
    fileLoad = new QAction("Load", this);
    fileLoad->setShortcut(QString("Ctrl+L"));
    connect(fileLoad, &QAction::triggered, this, &App::loadFile);

    fileSave = new QAction("Save", this);
    fileSave->setShortcut(QString("Ctrl+S"));
    connect(fileSave, &QAction::triggered, this, &App::saveFile);

    imageExport = new QAction("Export", this);
    imageExport->setShortcut(QString("Ctrl+E"));
    connect(imageExport, &QAction::triggered, this, &App::exportImage);

    undoAction = new QAction("Undo", this);
    undoAction->setShortcut(QString("Ctrl+Z"));
    connect(undoAction, &QAction::triggered, this, &App::undo);

    addSequenceTab = new QAction("Add Sequence", this);
    addSequenceTab->setShortcut(QString("Ctrl+D"));
    connect(addSequenceTab, &QAction::triggered, this, &App::addSequenceDiagramDialog);
}

void App::createMainMenu()
{
    mainMenu = menuBar()->addMenu("File");
    mainMenu->addAction(fileLoad);
    mainMenu->addAction(fileSave);
    mainMenu->addAction(imageExport);

    editMenu = menuBar()->addMenu("Edit");
    editMenu->addAction(undoAction);
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
    UMLModel *umlModel = ModelProvider::getInstance().getModel();
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", DEFAULT_PATH, "JSON (*.json)");
    qInfo() << fileName;
    if (fileName.length() == 0)
    {
        return; // User closed the dialog
    }
    umlModel->clear();
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

    // TODO:
    /*
    UMLData *data = new UMLData();
    bool loadSuccesfull = data->load(doc.object());
    UMLModel = data->toModel();
    delete data;
    */


    bool loadedSuccesfully = umlModel->loadData(json);

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
    QJsonObject root = ModelProvider::getInstance().getModel()->getSaveData();
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

void App::undo()
{
    CommandStack::getInstance().undo();
    scene->update();
}

void App::addSequenceDiagram(UMLSequenceModel *umlSequenceModel)
{
    SequenceDiagramView *sequenceView = new SequenceDiagramView(this, umlSequenceModel);
    QGraphicsScene *sequenceScene = new QGraphicsScene(sequenceView);
    sequenceScene->setSceneRect(0, 0, SCENE_SIZE, SCENE_SIZE);
    sequenceView->setMinimumSize(600, 600);
    sequenceView->setScene(sequenceScene);
    sequenceView->setDragMode(QGraphicsView::RubberBandDrag);
    sequenceView->setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing);
    sequenceView->setContextMenuPolicy(Qt::ActionsContextMenu);

    tabWidget->addTab(sequenceView, umlSequenceModel->getName());
    qDebug() << "added " << umlSequenceModel->getName();
}

void App::removeSequenceDiagram(int tabIndex)
{
    SequenceDiagramView *sequenceView = static_cast<SequenceDiagramView *>(tabWidget->widget(tabIndex));
    UMLSequenceModel *umlSequenceModel = sequenceView->getUMLSequenceModel();
    QString message = QString("Do you want to delete \"%1\" sequence diagram?").arg(umlSequenceModel->getName());
    QMessageBox::StandardButton dialogReply = QMessageBox::question(this, "Remove sequence diagram", message, QMessageBox::Yes|QMessageBox::No);
    if (dialogReply == QMessageBox::Yes)
    {
        tabWidget->removeTab(tabIndex);
        ModelProvider::getInstance().getModel()->removeSequence(umlSequenceModel);
    }
}

void App::addSequenceDiagramDialog()
{
    NewSequenceDialog *newClassDialog = new NewSequenceDialog();
    newClassDialog->show();
}
