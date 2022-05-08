/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file editinstancecommand.cpp
 * @author Michal Trlica (xtrlic02)
 */
#include "editinstancecommand.h"

EditInstanceCommand::EditInstanceCommand(UMLInstanceModel *umlInstanceModel, QString newName)
    : umlInstanceModel(umlInstanceModel),
      newName(newName), oldName(umlInstanceModel->getName())
{}

// - - - - - private - - - - -

void EditInstanceCommand::process()
{
    umlInstanceModel->setName(newName);
}

void EditInstanceCommand::undo()
{
    umlInstanceModel->setName(oldName);
}
