/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file dataprovider.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include "umldata.h"

/**
 * @brief Singleton, serving as single source of truth, providing easy access to UMLData model.
 */
class DataProvider
{
public:
    static DataProvider& getInstance();
    void setUMLData(UMLData *umlData);
    UMLData* getUMLData();

    DataProvider(DataProvider const&) = delete;
    void operator=(DataProvider const&) = delete;
private:
    DataProvider() {}

    UMLData *umlData;
};

#endif // DATAPROVIDER_H
