#ifndef UMLPARAMETERMODEL_H
#define UMLPARAMETERMODEL_H

#include <QString>
#include <QObject>
#include <QJsonObject>

class UMLParameterModel : public QObject
{
    Q_OBJECT
public:
    UMLParameterModel(QString name, QString type);
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

#endif // UMLPARAMETERMODEL_H
