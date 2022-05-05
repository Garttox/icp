#include "umlfielddata.h"

UMLFieldData::UMLFieldData(QString name, QString type, UMLAccessType access) :
    UMLAttribute(name, type, access)
{}

UMLFieldData::UMLFieldData(const UMLFieldData &original) :
    UMLAttribute(original.name, original.type, original.access)
{}

QString UMLFieldData::toString() const
{
    return QString("%1 %2: %3").arg(access.toAnnotationString(), name, type);
}

QJsonObject UMLFieldData::getSaveData()
{
    QJsonObject object;
    object.insert("name", name);
    object.insert("type", type);
    object.insert("access", access.toString());
    return object;
}
