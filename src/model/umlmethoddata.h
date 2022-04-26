#ifndef UMLMETHODDATA_H
#define UMLMETHODDATA_H

#include <QVector>
#include <QObject>

#include "umlidentifier.h"
class UMLMethodParameterData;

class UMLMethodData : public QObject, public UMLIdentifier
{
    Q_OBJECT
public:
    UMLMethodData(QString name, QString type, UMLAccessType *access);
    ~UMLMethodData();
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
