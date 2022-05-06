/**
 * ICP - UML Application
 * @date 25/4/2022
 * @file modelprovider.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "modelprovider.h"

ModelProvider& ModelProvider::getInstance()
{
    static ModelProvider instance;
    return instance;
}

void ModelProvider::setModel(UMLModel *umlModel)
{
    this->umlModel = umlModel;
}

UMLModel* ModelProvider::getModel()
{
    return this->umlModel;
}
