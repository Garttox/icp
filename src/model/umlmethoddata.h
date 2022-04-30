#ifndef UMLMETHODDATA_H
#define UMLMETHODDATA_H

#include <QVector>
#include <QObject>

#include "umlidentifier.h"
#include "umlmethodparameterdata.h"

class UMLMethodData : public UMLIdentifier
{
    Q_OBJECT
public:
    UMLMethodData(QString name, QString type, UMLAccessType access);
    UMLMethodData(const UMLMethodData &original);
    ~UMLMethodData();
    bool loadData(QJsonObject jsonMethodData);
    QJsonObject getSaveData();
    void addParameter(UMLMethodParameterData *parameter);
    QString toString() const override;
    QList<UMLMethodParameterData *> getParameters() const;
    void clearParameters();
public slots:
    void parameterModelChanged();
signals:
    void modelChanged(UMLMethodData* umlMethodData);
private:
    QList<UMLMethodParameterData *> parameters;
};

#endif // UMLMETHODDATA_H
