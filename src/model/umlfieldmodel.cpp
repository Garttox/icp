#include "umlfieldmodel.h"

UMLFieldModel::UMLFieldModel(QString name, QString type, UMLAccessType access) :
    UMLAttribute(name, type, access)
{}

UMLFieldModel::UMLFieldModel(const UMLFieldModel &original) :
    UMLAttribute(original.name, original.type, original.access)
{}

QString UMLFieldModel::toString() const
{
    return QString("%1 %2: %3").arg(access.toAnnotationString(), name, type);
}

QJsonObject UMLFieldModel::getSaveData()
{
    QJsonObject object;
    object.insert("name", name);
    object.insert("type", type);
    object.insert("access", access.toString());
    return object;
}
