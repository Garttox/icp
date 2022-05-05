/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umlclassdata.h
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

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
    UMLClassData(const UMLClassData &original);
    ~UMLClassData();
    void setData(const UMLClassData &data);
    bool loadData(QJsonObject jsonClassData);
    QJsonObject getSaveData();
    void setName(QString name);
    void setPosX(int x);
    void setPosY(int y);
    void addField(UMLFieldData *field);
    void addMethod(UMLMethodData *method);
    void removeFieldAt(int index);
    void removeMethodAt(int index);
    bool haveIdentifierWithSignature(QString signature) const;
    QString getName() const;
    UMLClassType getType() const;
    QString getDisplayName() const;
    UMLFieldData *getFieldAt(int index) const;
    UMLMethodData *getMethodAt(int index) const;
    UMLMethodData *findMethodByName(QString methodName) const;
    QList<UMLMethodData *> getMethods() const;
    QList<UMLFieldData *> getFields() const;
    QSet<UMLAttribute *> getIdentifiers() const;
    int getPosX() const;
    int getPosY() const;
    

public slots:
    void fieldModelChanged();
    void methodModelChanged();

signals:
    void modelChanged(UMLClassData *umlClassData);

private:
    QString name;
    UMLClassType type;
    int posX;
    int posY;
    QList<UMLFieldData *> fields;
    QList<UMLMethodData *> methods;
};

#endif // UMLCLASSDATA_H
