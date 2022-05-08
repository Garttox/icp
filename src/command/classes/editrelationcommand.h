/**
 * ICP - UML Application
 * @date 6/5/2022
 * @file editrelationcommand.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef EDITRELATIONCOMMAND_H
#define EDITRELATIONCOMMAND_H

#include "command/command.h"
#include "model/umlrelationmodel.h"
#include "model/umlrelationtype.h"

class EditRelationCommand : public Command
{
public:
    EditRelationCommand(UMLRelationModel *umlRelationModel, UMLRelationType newType);

private:
    virtual void process() override;
    virtual void undo() override;

    UMLRelationModel *umlRelationModel;
    UMLRelationType newType;
    UMLRelationType oldType;
};

#endif // EDITRELATIONCOMMAND_H
