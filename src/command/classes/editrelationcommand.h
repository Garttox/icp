#ifndef EDITRELATIONCOMMAND_H
#define EDITRELATIONCOMMAND_H

#include "command/command.h"
#include "model/umlrelationdata.h"
#include "model/umlrelationtype.h"

class EditRelationCommand : public Command
{
public:
    EditRelationCommand(UMLRelationData *umlRelationData, UMLRelationType newType);

private:
    virtual void process() override;
    virtual void undo() override;

    UMLRelationData *umlRelationData;
    UMLRelationType newType;
    UMLRelationType oldType;
};

#endif // EDITRELATIONCOMMAND_H
