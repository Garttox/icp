/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file addcallcommand.cpp
 * @author Michal Trlica (xtrlic02)
 */
#include "addcallcommand.h"

AddCallCommand::AddCallCommand(UMLSequenceModel *umlSequenceModel, UMLCallModel *umlCallModel)
    : umlSequenceModel(umlSequenceModel), umlCallModel(umlCallModel)
{}

// - - - - - private - - - - -

void AddCallCommand::process()
{
    umlSequenceModel->addCall(umlCallModel);
}

void AddCallCommand::undo()
{
    umlSequenceModel->removeCall(umlCallModel);
}
