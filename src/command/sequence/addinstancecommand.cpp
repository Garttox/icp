#include "addinstancecommand.h"

AddInstanceCommand::AddInstanceCommand(UMLSequenceModel *umlSequenceModel, UMLInstanceModel *umlInstanceModel)
    : umlSequenceModel(umlSequenceModel), umlInstanceModel(umlInstanceModel)
{}

// - - - - - private - - - - -

void AddInstanceCommand::process()
{
    umlSequenceModel->addInstance(umlInstanceModel);
}

void AddInstanceCommand::undo()
{
    umlSequenceModel->removeInstance(umlInstanceModel);
}
