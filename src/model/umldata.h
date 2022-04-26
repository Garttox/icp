#ifndef UMLDATA_H
#define UMLDATA_H

#include <QSet>
#include <QObject>

class UMLClassData;
class UMLRelationData;

class UMLData : public QObject
{
    Q_OBJECT
public:
    UMLData();
    ~UMLData();
    void addClass(UMLClassData *classData);
    void addRelation(UMLRelationData *relation);
    void clearData();
    UMLClassData* findClassByName(QString clsName);
    QSet<UMLClassData *> *getClasses();
public slots:
    void classModelChanged();
    void relationModelChanged();
signals:
    void classModelAdded(UMLClassData *classData);
private:
    QSet<UMLClassData *> *classes;
    QSet<UMLRelationData *> *relations;
};

#endif // UMLDATA_H
