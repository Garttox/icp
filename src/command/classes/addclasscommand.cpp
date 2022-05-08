/**
 * ICP - UML Application
 * @date 6/5/2022
 * @file addclasscommand.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "addclasscommand.h"
#include "model/modelprovider.h"
#include "model/umlmodel.h"

AddClassCommand::AddClassCommand(UMLClassModel *umlClassModel) :
    umlClassModel(umlClassModel)
{}

void AddClassCommand::process()
{
    UMLModel *umlModel = ModelProvider::getInstance().getModel();
    umlModel->addClass(umlClassModel);
}

void AddClassCommand::undo()
{
    UMLModel *umlModel = ModelProvider::getInstance().getModel();
    umlModel->removeClass(umlClassModel);
}
