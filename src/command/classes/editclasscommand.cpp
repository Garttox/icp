#include "editclasscommand.h"

EditClassCommand::EditClassCommand(UMLClassData *umlClassData, UMLClassData *umlClassDataEdited) :
    umlClassData(umlClassData),
    umlClassDataEdited(umlClassDataEdited)
{}

EditClassCommand::~EditClassCommand()
{
    delete umlClassDataEdited;
    delete umlClassDataOld;
}

void EditClassCommand::process()
{
    umlClassDataOld = new UMLClassData(*umlClassData);
    umlClassData->setData(*umlClassDataEdited);
}

void EditClassCommand::undo()
{
    umlClassData->setData(*umlClassDataOld);
}
