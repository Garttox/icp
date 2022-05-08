#include "moveinstancecommand.h"

#include <command/commandstack.h>

MoveInstanceCommand::MoveInstanceCommand(UMLInstanceModel *umlInstanceModel, QPoint newLocation)
    : newLocation(newLocation), umlInstanceModel(umlInstanceModel)
{}

void MoveInstanceCommand::process()
{
    oldLocation = QPoint(umlInstanceModel->getPosX(), umlInstanceModel->getPosY());
    umlInstanceModel->setPosX(newLocation.x());
    umlInstanceModel->setPosY(newLocation.y());

    // If item was not actually moved, then do not store this command
    if (oldLocation == newLocation)
    {
        CommandStack::getInstance().undo();
    }
}

void MoveInstanceCommand::undo()
{
    umlInstanceModel->setPosX(oldLocation.x());
    umlInstanceModel->setPosY(oldLocation.y());
}
