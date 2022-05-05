#include "addrelationcommand.h"
#include "model/dataprovider.h"
#include "model/umldata.h"

AddRelationCommand::AddRelationCommand(UMLRelationData * const umlRelationData) :
    umlRelationData(umlRelationData)
{}

// - - - - - private - - - - -

void AddRelationCommand::process()
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    umlData->addRelation(umlRelationData);
}

void AddRelationCommand::undo()
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    umlData->removeRelation(umlRelationData);
}
