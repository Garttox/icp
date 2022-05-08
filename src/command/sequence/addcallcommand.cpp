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
