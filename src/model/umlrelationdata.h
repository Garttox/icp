#ifndef UMLRELATIONDATA_H
#define UMLRELATIONDATA_H

class UMLClassData;
class UMLRelationType;

class UMLRelationData
{
public:
    UMLRelationData(UMLClassData *source, UMLClassData *destination, UMLRelationType *type);
private:
    UMLClassData *source;
    UMLClassData *destination;
    UMLRelationType *type;
};

#endif // UMLRELATIONDATA_H
