#include "umlfielddata.h"
#include "umlaccesstype.h"

UMLFieldData::UMLFieldData(QString name, QString type, UMLAccessType *access) :
    UMLIdentifier(name, type, access)
{}

QString UMLFieldData::toString()
{
    return QString("%1 %2: %3").arg(access->toString(), name, type);
}
