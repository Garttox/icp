/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlparametermodel.h
 * @author Michal Trlica (xtrlic02)
 */
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

signals:
    void modelChanged();

private:
    QString name;
    QString type;
};

#endif // UMLPARAMETERMODEL_H
