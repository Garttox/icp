#include "moveclasscommand.h"
#include "command/commandstack.h"

MoveClassCommand::MoveClassCommand(UMLClassData *umlClassData, QPoint newPosition) :
    newPosition(newPosition),
    umlClassData(umlClassData)
{}

void MoveClassCommand::process()
{
    oldPosition = QPoint(umlClassData->getPosX(), umlClassData->getPosY());
    umlClassData->setPosition(newPosition.x(), newPosition.y());

    // If item was not actually moved, then do not store this command
    if (oldPosition == newPosition)
    {
        CommandStack::getInstance().undo();
    }
}

void MoveClassCommand::undo()
{
    umlClassData->setPosition(oldPosition.x(), oldPosition.y());
}
