#ifndef UMLMETHODDATA_H
#define UMLMETHODDATA_H

#include <QVector>
#include <QObject>

#include "umlidentifier.h"
#include "umlmethodparameterdata.h"

class UMLMethodData : public QObject, public UMLIdentifier
{
    Q_OBJECT
public:
    UMLMethodData(QString name, QString type, UMLAccessType access);
    ~UMLMethodData();
    bool loadData(QJsonObject jsonMethodData);
    void addParameter(UMLMethodParameterData *parameter);
    QString toString();
public slots:
    void parameterModelChanged();
signals:
    void modelChanged();
private:
    QVector<UMLMethodParameterData *> parameters;
};

#endif // UMLMETHODDATA_H
