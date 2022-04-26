#ifndef UMLMETHODPARAMETERDATA_H
#define UMLMETHODPARAMETERDATA_H

#include <QString>
#include <QObject>

class UMLMethodParameterData : public QObject
{
    Q_OBJECT
public:
    UMLMethodParameterData(QString name, QString type);
    QString toString();
signals:
    void modelChanged();
private:
    QString name;
    QString type;
};

#endif // UMLMETHODPARAMETERDATA_H
