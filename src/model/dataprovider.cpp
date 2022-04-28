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
