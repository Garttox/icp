#include "app.h"
#include "ui_app.h"
#include <QFileDialog>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

App::App(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::App)
{
    ui->setupUi(this);
}

App::~App()
{
    delete ui;
}

void App::on_actionLoad_triggered()
{
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
    for (QJsonValueRef el : json["classes"].toArray()) {
        qInfo() << el.toObject()["name"].toString();
    }
}

