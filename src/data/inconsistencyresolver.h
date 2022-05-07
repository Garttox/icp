/**
 * ICP - UML Application
 * @date 2/5/2022
 * @file inconsistencyresolver.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef INCONSISTENCYRESOLVER_H
#define INCONSISTENCYRESOLVER_H

#include "data.h"
#include "umldata.h"

/**
 * @brief Class for resolving inconsistencies in loaded data.
 */
class InconsistencyResolver
{
public:
    InconsistencyResolver();

    /**
     * @brief Resolves all inconsistencies of given UMLData.
     * @param umlData UMLData to be resolved.
     * @return List of strings describing resolved inconsistencies for user.
     */
    QStringList resolve(UMLData *umlData);

private:
    QStringList resolved;

};

#endif // INCONSISTENCYRESOLVER_H
