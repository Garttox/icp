/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file movecallcommand.cpp
 * @author Michal Trlica (xtrlic02)
 */
#include "movecallcommand.h"

#include <command/commandstack.h>

MoveCallCommand::MoveCallCommand(UMLCallModel *umlCallModel, int newAtTime)
    : umlCallModel(umlCallModel), newAtTime(newAtTime), oldAtTime(umlCallModel->getAtTime())
{}

void MoveCallCommand::process()
{
    umlCallModel->setAtTime(newAtTime);

    // If item was not actually moved, then do not store this command
    if (oldAtTime == newAtTime)
    {
        CommandStack::getInstance().undo();
    }
}

void MoveCallCommand::undo()
{
    umlCallModel->setAtTime(oldAtTime);
}
