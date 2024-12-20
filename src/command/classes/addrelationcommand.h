/**
 * ICP - UML Application
 * @date 6/5/2022
 * @file addrelationcommand.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef ADDRELATIONCOMMAND_H
#define ADDRELATIONCOMMAND_H

#include "command/command.h"
#include "model/umlrelationmodel.h"

class AddRelationCommand : public Command
{
public:
    AddRelationCommand(UMLRelationModel *const umlRelationModel);

private:
    virtual void process() override;
    virtual void undo() override;

    UMLRelationModel *const umlRelationModel;
};

#endif // ADDRELATIONCOMMAND_H
