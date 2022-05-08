/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlattribute.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef UMLATTRIBUTEH_H
#define UMLATTRIBUTEH_H

#include <QString>
#include <QObject>

#include "umlaccesstype.h"

class UMLAttribute : public QObject
{
    Q_OBJECT
public:
    UMLAttribute(QString name, QString type, UMLAccessType access);
    ~UMLAttribute();
    QString getName() const;
    QString getType() const;
    UMLAccessType getAccess() const;
    virtual QString toString() const;
    void setName(QString name);
    void setType(QString type);
    void setAccess(UMLAccessType access);
protected:
    QString name;
    QString type;
    UMLAccessType access;
signals:
    void modelChanged(UMLAttribute* identifier);
};

#endif // UMLATTRIBUTEH_H
