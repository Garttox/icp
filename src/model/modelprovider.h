/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file modelprovider.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef MODELPROVIDER_H
#define MODELPROVIDER_H

#include "umlmodel.h"

/**
 * @brief Singleton, serving as single source of truth, providing easy access to UML model.
 */
class ModelProvider
{
public:
    ModelProvider(ModelProvider const&) = delete;
    void operator=(ModelProvider const&) = delete;

    static ModelProvider& getInstance();
    void setModel(UMLModel *umlModel);
    UMLModel* getModel();

private:
    ModelProvider() {}
    UMLModel *umlModel;

};

#endif // MODELPROVIDER_H
