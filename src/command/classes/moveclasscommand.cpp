#include "moveclasscommand.h"
#include "command/commandstack.h"

MoveClassCommand::MoveClassCommand(UMLClassModel *umlClassModel, QPoint newPosition) :
    newPosition(newPosition),
    umlClassModel(umlClassModel)
{}

void MoveClassCommand::process()
{
    oldPosition = QPoint(umlClassModel->getPosX(), umlClassModel->getPosY());
    umlClassModel->setPosition(newPosition.x(), newPosition.y());

    // If item was not actually moved, then do not store this command
    if (oldPosition == newPosition)
    {
        CommandStack::getInstance().undo();
    }
}

void MoveClassCommand::undo()
{
    umlClassModel->setPosition(oldPosition.x(), oldPosition.y());
}
