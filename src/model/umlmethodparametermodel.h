#ifndef UMLMETHODPARAMETERMODEL_H
#define UMLMETHODPARAMETERMODEL_H

#include <QString>
#include <QObject>
#include <QJsonObject>

class UMLMethodParameterModel : public QObject
{
    Q_OBJECT
public:
    UMLMethodParameterModel(QString name, QString type);
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

#endif // UMLMETHODPARAMETERMODEL_H
