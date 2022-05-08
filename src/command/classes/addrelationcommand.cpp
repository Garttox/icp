/**
 * ICP - UML Application
 * @date 6/5/2022
 * @file addrelationcommand.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "addrelationcommand.h"
#include "model/modelprovider.h"
#include "model/umlmodel.h"

AddRelationCommand::AddRelationCommand(UMLRelationModel * const umlRelationModel) :
    umlRelationModel(umlRelationModel)
{}

// - - - - - private - - - - -

void AddRelationCommand::process()
{
    UMLModel *umlModel = ModelProvider::getInstance().getModel();
    umlModel->addRelation(umlRelationModel);
}

void AddRelationCommand::undo()
{
    UMLModel *umlModel = ModelProvider::getInstance().getModel();
    umlModel->removeRelation(umlRelationModel);
}
