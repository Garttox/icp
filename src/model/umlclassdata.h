#ifndef UMLCLASSDATA_H
#define UMLCLASSDATA_H

#include <QString>
#include <QSet>
#include <QObject>

#include "umlfielddata.h"
#include "umlmethoddata.h"

enum class UMLClassType
{
    CLASS,
    INTERFACE
};

class UMLClassData : public QObject
{
    Q_OBJECT
public:
    UMLClassData(QString name, UMLClassType type, int posX, int posY);
    ~UMLClassData();
    void addField(UMLFieldData *field);
    void addMethod(UMLMethodData *method);
    QString getName();
    QSet<UMLMethodData *> *getMethods();
    QSet<UMLFieldData *> *getFields();
    int getPosX();
    int getPosY();
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
    QSet<UMLFieldData *> *fields;
    QSet<UMLMethodData *> *methods;
};

#endif // UMLCLASSDATA_H
