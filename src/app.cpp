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

#include "app.h"
#include "view\diagramgraphicsview.h"
#include "view\classes\umlclass.h"
#include "model\umldata.h"
#include "model\umlclassdata.h"
#include "model\umlfielddata.h"
#include "model\umlmethoddata.h"
#include "model\umlaccesstype.h"
#include "model\umlmethodparameterdata.h"
#include "model\umlrelationtype.h"
#include "model\umlrelationdata.h"
#include "model\dataprovider.h"
#include "view\classes\newclassdialog.h"
#include "ui_newclassdialog.h"

App::App(QWidget *parent) :
    QMainWindow(parent)
{
    UMLData* umlData = new UMLData();
    DataProvider::getInstance().setUMLData(umlData);

    tabWidget = new QTabWidget(this);
    view = new ClassDiagramGraphicsView(this);
    scene = new QGraphicsScene(view);
    scene->setSceneRect(0, 0, 1000, 1000);
    view->setMinimumSize(600, 600);
    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setRenderHints(QPainter::Antialiasing
                         | QPainter::TextAntialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    //setCentralWidget(view);

    /*QToolBar *toolbar=new QToolBar("toolbar",view);

    toolbar->addAction("action1");
    toolbar->addAction("action2");
    toolbar->setBackgroundRole(QPalette::Base); */
    tabWidget->addTab(view, QString("Class Diagram"));
    setCentralWidget(tabWidget);

    createActions();
    createMainMenu();
    createToolBar();

    setWindowTitle(tr("UMLiBubli"));
}

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
}

//SLOTS

void App::loadFile()
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();

    QString fileName = QFileDialog::getOpenFileName(this, "Open a file");
    qInfo() << fileName;
    QJsonDocument doc;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "failed to read the file";
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Error occured while reading the file");
        messageBox.setFixedSize(500,200);
        return;
    }
    QByteArray byteFile = file.readAll();
    doc = QJsonDocument::fromJson(byteFile);
    QJsonObject json = doc.object();

    // read classes
    foreach (auto clsEl, json["classes"].toArray())
    {
        qInfo() << clsEl.toObject()["name"].toString();

        QString name = clsEl.toObject()["name"].toString();
        UMLClassType type = clsEl.toObject()["type"].toString() == "CLASS" ? UMLClassType::CLASS : UMLClassType::INTERFACE;
        int posX = clsEl.toObject()["posX"].toInt();
        int posY = clsEl.toObject()["posY"].toInt();
        UMLClassData *classData = new UMLClassData(name, type, posX, posY);

        // read fields
        foreach (auto fieldEl, clsEl.toObject()["fields"].toArray())
        {
            qInfo() << "    Field:" << fieldEl.toObject()["name"].toString();

            QString name = fieldEl.toObject()["name"].toString();
            QString type = fieldEl.toObject()["type"].toString();
            UMLAccessType *access = new UMLAccessType(fieldEl.toObject()["type"].toString());
            UMLFieldData *field = new UMLFieldData(name, type, access);
            classData->addField(field);
        }

        // read methods
        foreach (auto methodEl, clsEl.toObject()["methods"].toArray())
        {
            qInfo() << "    Method:" << methodEl.toObject()["name"].toString();

            QString name = methodEl.toObject()["name"].toString();
            QString type = methodEl.toObject()["type"].toString();
            UMLAccessType *access = new UMLAccessType(methodEl.toObject()["type"].toString());
            UMLMethodData *method = new UMLMethodData(name, type, access);
            // read method parameters
            foreach (auto parameterEl, methodEl.toObject()["parameters"].toArray())
            {
                qInfo() << "        " << parameterEl.toObject()["name"].toString();

                QString name = parameterEl.toObject()["name"].toString();
                QString type = parameterEl.toObject()["type"].toString();
                UMLMethodParameterData *parameter = new UMLMethodParameterData(name, type);
                method->addParameter(parameter);
            }

            classData->addMethod(method);
        }
        umlData->addClass(classData);
        UMLClass *cls = new UMLClass(classData);
        cls->setPos(QPoint(classData->getPosX(), classData->getPosY()));
        scene->addItem(cls);
        scene->clearSelection();
    }


    // read relations
    foreach (auto relationEl, json["relations"].toArray())
    {
        qInfo() << relationEl.toObject()["source"].toString() << " to " << relationEl.toObject()["destination"].toString();

        UMLClassData *source = umlData->findClassByName(relationEl.toObject()["source"].toString());
        UMLClassData *destination = umlData->findClassByName(relationEl.toObject()["destination"].toString());
        UMLRelationType *type = new UMLRelationType(relationEl.toObject()["type"].toString());
        UMLRelationData *relation = new UMLRelationData(source, destination, type);

        umlData->addRelation(relation);
    }
}
void App::saveFile()
{
    //TODO: saving to file
}

void App::addClass()
{

    /*UMLClass *cls = new UMLClass();
    cls->setPos(QPoint(10, 10));
    scene->addItem(cls);
    scene->clearSelection();*/

    NewClassDialog *newClassDialog = new NewClassDialog();
    newClassDialog->show();
}
