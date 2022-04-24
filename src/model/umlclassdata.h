#ifndef UMLCLASSDATA_H
#define UMLCLASSDATA_H

#include <QString>
#include <QSet>

class UMLFieldData;
class UMLMethodData;

enum UMLClassType
{
    CLASS,
    INTERFACE
};

class UMLClassData
{
public:
    UMLClassData(QString name, UMLClassType type, int posX, int posY);
    ~UMLClassData();
    void addField(UMLFieldData *field);
    void addMethod(UMLMethodData *method);
    QString getName();
private:
    QString name;
    UMLClassType type;
    int posX;
    int posY;
    QSet<UMLFieldData *> fields;
    QSet<UMLMethodData *> methods;
};

#endif // UMLCLASSDATA_H
