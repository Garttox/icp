/**
 * ICP - UML Application
 * @date 1/5/2022
 * @file umlattributedata.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "umlattributedata.h"

QString UMLAttributeData::getName() const
{
    return name;
}

QString UMLAttributeData::getType() const
{
    return type;
}

QString UMLAttributeData::getAccess() const
{
    return access;
}
