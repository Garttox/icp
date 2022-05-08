#include "moveinstancecommand.h"

#include <command/commandstack.h>

MoveInstanceCommand::MoveInstanceCommand(UMLInstanceModel *umlInstanceModel, int newPosX)
    : oldPosX(umlInstanceModel->getPosX()), newPosX(newPosX), umlInstanceModel(umlInstanceModel)
{}

void MoveInstanceCommand::process()
{
    umlInstanceModel->setPosX(newPosX);

    // If item was not actually moved, then do not store this command
    if (oldPosX == newPosX)
    {
        CommandStack::getInstance().undo();
    }
}

void MoveInstanceCommand::undo()
{
    umlInstanceModel->setPosX(oldPosX);
}
