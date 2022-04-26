#ifndef UMLDATA_H
#define UMLDATA_H

#include <QSet>

class UMLClassData;
class UMLRelationData;

class UMLData
{
public:
    UMLData();
    ~UMLData();
    void addClass(UMLClassData *cls);
    void addRelation(UMLRelationData *relation);
    void clearData();
    UMLClassData* findClassByName(QString clsName);
    QSet<UMLClassData *> *getClasses();
private:
    QSet<UMLClassData *> *classes;
    QSet<UMLRelationData *> *relations;
};

#endif // UMLDATA_H
