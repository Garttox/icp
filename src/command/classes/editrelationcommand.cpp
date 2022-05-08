/**
 * ICP - UML Application
 * @date 6/5/2022
 * @file editrelationcommand.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "editrelationcommand.h"

EditRelationCommand::EditRelationCommand(UMLRelationModel *umlRelationModel, UMLRelationType newType) :
    umlRelationModel(umlRelationModel),
    newType(newType),
    oldType(umlRelationModel->getType())
{}

void EditRelationCommand::process()
{
    umlRelationModel->setType(newType);
}

void EditRelationCommand::undo()
{
    umlRelationModel->setType(oldType);
}

