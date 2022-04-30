#ifndef UMLIDENTIFIER_H
#define UMLIDENTIFIER_H

#include <QString>
#include <QObject>

#include "umlaccesstype.h"

class UMLIdentifier : public QObject
{
    Q_OBJECT
public:
    UMLIdentifier(QString name, QString type, UMLAccessType access);
    ~UMLIdentifier();
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
    void modelChanged(UMLIdentifier* identifier);
};

#endif // UMLIDENTIFIER_H
