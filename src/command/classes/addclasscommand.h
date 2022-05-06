#ifndef ADDCLASSCOMMAND_H
#define ADDCLASSCOMMAND_H

#include "command/command.h"
#include "model/umlclassmodel.h"

class AddClassCommand : public Command
{
public:
    AddClassCommand(UMLClassModel *umlClassModel);

private:
    virtual void process() override;
    virtual void undo() override;

    UMLClassModel *const umlClassModel;
};

#endif // ADDCLASSCOMMAND_H
