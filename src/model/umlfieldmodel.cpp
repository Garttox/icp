/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file umlfieldmodel.cpp
 * @author Michal Trlica (xtrlic02)
 */
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
