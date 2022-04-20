/********************************************************************************
** Form generated from reading UI file 'app.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP_H
#define UI_APP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_App
{
public:
    QAction *actionLoad;
    QAction *actionSave;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuLoad;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *App)
    {
        if (App->objectName().isEmpty())
            App->setObjectName(QStringLiteral("App"));
        App->resize(400, 300);
        actionLoad = new QAction(App);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionSave = new QAction(App);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralWidget = new QWidget(App);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        App->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(App);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 20));
        menuLoad = new QMenu(menuBar);
        menuLoad->setObjectName(QStringLiteral("menuLoad"));
        App->setMenuBar(menuBar);
        mainToolBar = new QToolBar(App);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        App->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(App);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        App->setStatusBar(statusBar);

        menuBar->addAction(menuLoad->menuAction());
        menuLoad->addAction(actionLoad);
        menuLoad->addAction(actionSave);

        retranslateUi(App);

        QMetaObject::connectSlotsByName(App);
    } // setupUi

    void retranslateUi(QMainWindow *App)
    {
        App->setWindowTitle(QApplication::translate("App", "App", 0));
        actionLoad->setText(QApplication::translate("App", "Load", 0));
        actionSave->setText(QApplication::translate("App", "Save", 0));
        menuLoad->setTitle(QApplication::translate("App", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class App: public Ui_App {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP_H
