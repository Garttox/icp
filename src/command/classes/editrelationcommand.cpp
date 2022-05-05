#include "editrelationcommand.h"

EditRelationCommand::EditRelationCommand(UMLRelationData *umlRelationData, UMLRelationType newType) :
    umlRelationData(umlRelationData),
    newType(newType),
    oldType(umlRelationData->getType())
{}

void EditRelationCommand::process()
{
    umlRelationData->setType(newType);
}

void EditRelationCommand::undo()
{
    umlRelationData->setType(oldType);
}

