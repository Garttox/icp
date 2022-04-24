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

#include "app.h"
#include "ui\classes\umlclass.h"
#include "model\umldata.h"
#include "model\umlclassdata.h"
#include "model\umlfielddata.h"
#include "model\umlmethoddata.h"
#include "model\umlaccesstype.h"
#include "model\umlmethodparameterdata.h"
#include "model\umlrelationtype.h"
#include "model\umlrelationdata.h"

App::App(QWidget *parent) :
    QMainWindow(parent), umlData(new UMLData())
{
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(view);
    scene->setSceneRect(0, 0, 600, 500);
    view->setMinimumSize(400, 400);
    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setRenderHints(QPainter::Antialiasing
                         | QPainter::TextAntialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    setCentralWidget(view);

    createActions();
    createMainMenu();
    createToolBar();

    //umlData = new UMLData();

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
    umlData->clearData();

    QString fileName = QFileDialog::getOpenFileName(this, "Open a file");
    qInfo() << fileName;
    QJsonDocument doc;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "failed to read the file";
    }
    QByteArray byteFile = file.readAll();
    doc = QJsonDocument::fromJson(byteFile);
    QJsonObject json = doc.object();

    // read classes
    foreach (auto clsEl, json["classes"].toArray())
    {
        qInfo() << clsEl.toObject()["name"].toString();

        QString name = clsEl.toObject()["name"].toString();
        UMLClassType type = clsEl.toObject()["type"].toString() == "CLASS" ? CLASS : INTERFACE;
        int posX = clsEl.toObject()["posX"].toInt();
        int posY = clsEl.toObject()["posY"].toInt();
        UMLClassData *cls = new UMLClassData(name, type, posX, posY);

        // read fields
        foreach (auto fieldEl, clsEl.toObject()["fields"].toArray())
        {
            qInfo() << "    Field:" << fieldEl.toObject()["name"].toString();

            QString name = fieldEl.toObject()["name"].toString();
            QString type = fieldEl.toObject()["type"].toString();
            UMLAccessType *access = new UMLAccessType(UMLAccessType::toType(fieldEl.toObject()["type"].toString()));
            UMLFieldData *field = new UMLFieldData(name, type, access);
            cls->addField(field);
        }

        // read methods
        foreach (auto methodEl, clsEl.toObject()["methods"].toArray())
        {
            qInfo() << "    Method:" << methodEl.toObject()["name"].toString();

            QString name = methodEl.toObject()["name"].toString();
            QString type = methodEl.toObject()["type"].toString();
            UMLAccessType *access = new UMLAccessType(UMLAccessType::toType(methodEl.toObject()["type"].toString()));
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

            cls->addMethod(method);
        }

        umlData->addClass(cls);
    }

    // read relations
    foreach (auto relationEl, json["relations"].toArray())
    {
        qInfo() << relationEl.toObject()["source"].toString() << " to " << relationEl.toObject()["destination"].toString();

        UMLClassData *source = umlData->findClassByName(relationEl.toObject()["source"].toString());
        UMLClassData *destination = umlData->findClassByName(relationEl.toObject()["destination"].toString());
        UMLRelationType *type = new UMLRelationType(UMLRelationType::toType(relationEl.toObject()["type"].toString()));
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
    UMLClass *cls = new UMLClass;
    cls->setPos(QPoint(10, 10));
    scene->addItem(cls);
    scene->clearSelection();
}
