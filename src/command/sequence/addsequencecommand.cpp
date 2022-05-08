/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file addsequencecommand.cpp
 * @author Michal Trlica (xtrlic02)
 */
#include "addsequencecommand.h"

#include <model/modelprovider.h>
#include <model/umlmodel.h>

AddSequenceCommand::AddSequenceCommand(UMLSequenceModel *const umlSequenceModel)
    : umlSequenceModel(umlSequenceModel)
{}

// - - - - - private - - - - -

void AddSequenceCommand::process()
{
    UMLModel *umlModel = ModelProvider::getInstance().getModel();
    umlModel->addSequence(umlSequenceModel);
}

void AddSequenceCommand::undo()
{
    UMLModel *umlModel = ModelProvider::getInstance().getModel();
    umlModel->removeSequence(umlSequenceModel);
}
