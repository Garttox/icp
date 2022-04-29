#include <QFileDialog>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QSizePolicy>

#include "app.h"
#include "view\classdiagramgraphicsview.h"
#include "view\classes\umlclass.h"
#include "view\classes\newclassdialog.h"
#include "model\umldata.h"
#include "model\umlclassdata.h"
#include "model\umlfielddata.h"
#include "model\umlmethoddata.h"
#include "model\umlaccesstype.h"
#include "model\umlmethodparameterdata.h"
#include "model\umlrelationtype.h"
#include "model\umlrelationdata.h"
#include "model\dataprovider.h"
#include "ui_newclassdialog.h"

App::App(QWidget *parent) :
    QMainWindow(parent)
{
    UMLData* umlData = new UMLData();
    DataProvider::getInstance().setUMLData(umlData);

    tabWidget = new QTabWidget(this);
    view = new ClassDiagramGraphicsView(this);
    scene = new QGraphicsScene(view);
    scene->setSceneRect(0, 0, SCENE_SIZE, SCENE_SIZE);
    view->setMinimumSize(600, 600);
    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    // setCentralWidget(view);

    /*
    QToolBar *toolbar=new QToolBar("toolbar",view);
    toolbar->addAction("action1");
    toolbar->addAction("action2");
    toolbar->setBackgroundRole(QPalette::Base);
    */
    tabWidget->addTab(view, QString("Class Diagram"));
    setCentralWidget(tabWidget);

    createActions();
    createMainMenu();
    createToolBar();

    setWindowTitle(tr("UMLiBubli"));
}

//  - - - - - private  - - - - -

void App::createActions()
{
    fileLoad = new QAction(tr("&Load"), this);
    fileLoad->setShortcut(tr("Ctrl+L"));
    connect(fileLoad, SIGNAL(triggered()), this, SLOT(loadFile()));

    fileSave = new QAction(tr("&Save"), this);
    fileSave->setShortcut(tr("Ctrl+S"));
    connect(fileSave, SIGNAL(triggered()), this, SLOT(saveFile()));

    addClassAction = new QAction(tr("Add &class"), this);
    addClassAction->setShortcut(tr("Ctrl+N"));
    connect(addClassAction, SIGNAL(triggered()), this, SLOT(addClass()));

    addInterfaceAction = new QAction(tr("Add interface"), this);
    // addInterfaceAction->setShortcut(tr("Ctrl+N"));
    connect(addInterfaceAction, SIGNAL(triggered()), this, SLOT(addInterface()));

    removeSelectedAction = new QAction(tr("Remove"), this);
    removeSelectedAction->setShortcut(Qt::Key_Delete);
    connect(removeSelectedAction, SIGNAL(triggered()), this, SLOT(removeSelected()));
}

void App::createMainMenu()
{
    mainMenu = menuBar()->addMenu(tr("&File"));
    mainMenu->addAction(fileLoad);
    mainMenu->addAction(fileSave);
}

void App::createToolBar()
{
    toolBar = addToolBar(tr("Tools"));
    toolBar->addAction(addClassAction);
    toolBar->addAction(addInterfaceAction);
    toolBar->addAction(removeSelectedAction);
}

void App::removeSelectedRelations()
{
    QList<UMLRelation *> selected = getSelectedOfGivenType<UMLRelation*>();
    foreach(UMLRelation *item, selected)
    {
        item->remove();
    }
}

void App::removeSelectedClasses()
{
    QList<UMLClass *> selected = getSelectedOfGivenType<UMLClass*>();
    foreach(UMLClass *item, selected)
    {
        item->remove();
    }
}

template<class T>
QList<T> App::getSelectedOfGivenType()
{
    QList<T> filtered;
    foreach(QGraphicsItem *item, scene->selectedItems())
    {
        if (T casted = dynamic_cast<T>(item))
        {
            filtered.append(casted);
        }
    }
    return filtered;
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

void App::addClass()
{
    NewClassDialog *newClassDialog = new NewClassDialog(UMLClassType::CLASS);
    newClassDialog->show();
}

void App::addInterface()
{
    NewClassDialog *newClassDialog = new NewClassDialog(UMLClassType::INTERFACE);
    newClassDialog->show();
}

void App::removeSelected()
{
    removeSelectedRelations();
    removeSelectedClasses();
}
