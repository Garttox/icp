#ifndef UMLMETHODPARAMETERDATA_H
#define UMLMETHODPARAMETERDATA_H

#include <QString>
#include <QObject>
#include <QJsonObject>

class UMLMethodParameterData : public QObject
{
    Q_OBJECT
public:
    UMLMethodParameterData(QString name, QString type);
    QString toString() const;
    QString getName() const;
    QString getType() const;
    QJsonObject getSaveData();
signals:
    void modelChanged();
private:
    QString name;
    QString type;
};

#endif // UMLMETHODPARAMETERDATA_H
