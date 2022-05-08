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
#include <QString>
#include <QList>

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
    void resolveDuplicatedClassNames(UMLData *umlData);
    void resolveDuplicatedSequenceNames(UMLData *umlData);
    void resolveNonExistingMethodsForCalls(UMLData *umlData);
    void resolveNonExistingInstancesForCalls(UMLData *umlData);
    void resolveNonExistingClassesForInstances(UMLData *umlData);



    bool hasDuplicate(QStringList list);

    QStringList resolved;

};

#endif // INCONSISTENCYRESOLVER_H
