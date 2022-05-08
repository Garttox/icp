/**
 * ICP - UML Application
 * @date 6/5/2022
 * @file editclasscommand.cpp
 * @author Martin Bednář (xbedna77)
 */

#include "editclasscommand.h"

EditClassCommand::EditClassCommand(UMLClassModel *umlClassModel, UMLClassModel *umlClassModelEdited) :
    umlClassModel(umlClassModel),
    umlClassModelEdited(umlClassModelEdited)
{}

EditClassCommand::~EditClassCommand()
{
    delete umlClassModelEdited;
    delete umlClassModelOld;
}

void EditClassCommand::process()
{
    umlClassModelOld = new UMLClassModel(*umlClassModel);
    umlClassModel->setModel(*umlClassModelEdited);
}

void EditClassCommand::undo()
{
    umlClassModel->setModel(*umlClassModelOld);
}
