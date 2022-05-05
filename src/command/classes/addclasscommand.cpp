#include "addclasscommand.h"
#include "model/dataprovider.h"
#include "model/umldata.h"

AddClassCommand::AddClassCommand(UMLClassData *umlClassData) :
    umlClassData(umlClassData)
{}

AddClassCommand::~AddClassCommand()
{}

void AddClassCommand::process()
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    umlData->addClass(umlClassData);
}

void AddClassCommand::undo()
{
    UMLData *umlData = DataProvider::getInstance().getUMLData();
    umlData->removeClass(umlClassData);
}
