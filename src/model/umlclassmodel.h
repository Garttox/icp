/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file umlclassmodel.h
 * @authors Michal Trlica (xtrlic02), Martin Bednář (xbedna77)
 */

#ifndef UMLCLASSMODEL_H
#define UMLCLASSMODEL_H

#include <QString>
#include <QList>
#include <QObject>

#include "umlfieldmodel.h"
#include "umlmethodmodel.h"
#include "umlclasstype.h"

class UMLClassModel : public QObject
{
    Q_OBJECT
public:
    UMLClassModel(QString name, UMLClassType type, int posX, int posY);
    UMLClassModel(QString name, UMLClassType type, QList<UMLFieldModel*> fields,  QList<UMLMethodModel*> methods, int posX, int posY);
    UMLClassModel(const UMLClassModel &original);
    ~UMLClassModel();

    void setModel(UMLClassModel &model);
    void setName(QString name);
    void setPosition(int x, int y);
    void addField(UMLFieldModel *field);
    void addMethod(UMLMethodModel *method);
    void removeFieldAt(int index);
    void removeMethodAt(int index);
    bool haveIdentifierWithSignature(QString signature) const;

    QString getName() const;
    UMLClassType getType() const;
    QString getDisplayName() const;
    UMLFieldModel *getFieldAt(int index) const;
    UMLMethodModel *getMethodAt(int index) const;
    UMLMethodModel *findMethodByName(QString methodName) const;

    QList<UMLMethodModel *> getMethods() const;
    QList<UMLFieldModel *> getFields() const;
    QSet<UMLAttribute *> getIdentifiers() const;
    int getPosX() const;
    int getPosY() const;
    

public slots:
    void fieldModelChanged();
    void methodModelChanged();

signals:
    void modelChanged(UMLClassModel *umlClassModel);

private:
    /**
     * @brief Get and remove method with specific oid from methods list.
     * @param oid Original id to look for.
     * @return UMLMethodModel if found, nullptr otherwise.
     */
    UMLMethodModel *takeMethodByOid(QUuid oid);

    /**
     * @brief Does method merging based on oids, from foreign UMLClassModel to this UMLClassModel.
     * @param foreign UMLClassModel to be merged.
     */
    void setMethodsFromCopy(UMLClassModel &foreign);

    QString name;
    UMLClassType type;
    int posX;
    int posY;
    QList<UMLFieldModel *> fields;
    QList<UMLMethodModel *> methods;

};

#endif // UMLCLASSMODEL_H
