#ifndef UMLCLASSDATA_H
#define UMLCLASSDATA_H

#include <QString>
#include <QList>
#include <QObject>

#include "umlfielddata.h"
#include "umlmethoddata.h"
#include "umlclasstype.h"

class UMLClassData : public QObject
{
    Q_OBJECT
public:
    UMLClassData(QString name, UMLClassType type, int posX, int posY);
    ~UMLClassData();
    bool loadData(QJsonObject jsonClassData);
    void setName(QString name);
    void addField(UMLFieldData *field);
    void addMethod(UMLMethodData *method);
    void removeFieldAt(int index);
    void removeMethodAt(int index);
    QString getName() const;
    QString getDisplayName() const;
    UMLFieldData *getFieldAt(int index) const;
    UMLMethodData *getMethodAt(int index) const;
    QList<UMLMethodData *> *getMethods() const;
    QList<UMLFieldData *> *getFields() const;
    int getPosX() const;
    int getPosY() const;
    
public slots:
    void fieldModelChanged();
    void methodModelChanged();
signals:
    void modelChanged();
private:
    QString name;
    UMLClassType type;
    int posX;
    int posY;
    QList<UMLFieldData *> *fields;
    QList<UMLMethodData *> *methods;
};

#endif // UMLCLASSDATA_H
