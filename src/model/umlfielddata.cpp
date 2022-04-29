#include "umlfielddata.h"

UMLFieldData::UMLFieldData(QString name, QString type, UMLAccessType access) :
    UMLIdentifier(name, type, access)
{}

UMLFieldData::UMLFieldData(const UMLFieldData &original) :
    QObject(),
    UMLIdentifier(original.name, original.type, original.access)
{}

QString UMLFieldData::toString() const
{
    return QString("%1 %2: %3").arg(access.toString(), name, type);
}
