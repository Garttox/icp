#ifndef ADDRELATIONCOMMAND_H
#define ADDRELATIONCOMMAND_H

#include "command/command.h"
#include "model/umlrelationdata.h"

class AddRelationCommand : public Command
{
public:
    AddRelationCommand(UMLRelationData *const umlRelationData);

private:
    virtual ~AddRelationCommand();
    virtual void process() override;
    virtual void undo() override;

    UMLRelationData *const umlRelationData;
};

#endif // ADDRELATIONCOMMAND_H
