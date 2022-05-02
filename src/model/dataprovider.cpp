/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file dataprovider.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "dataprovider.h"

DataProvider& DataProvider::getInstance()
{
    static DataProvider instance;
    return instance;
}

void DataProvider::setUMLData(UMLData *umlData)
{
    this->umlData = umlData;
}

UMLData* DataProvider::getUMLData()
{
    return this->umlData;
}
