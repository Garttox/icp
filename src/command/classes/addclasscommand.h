#ifndef ADDCLASSCOMMAND_H
#define ADDCLASSCOMMAND_H

#include "command/command.h"
#include "model/umlclassdata.h"

class AddClassCommand : public Command
{
public:
    AddClassCommand(UMLClassData *umlClassData);

private:
    virtual void process() override;
    virtual void undo() override;

    UMLClassData *const umlClassData;
};

#endif // ADDCLASSCOMMAND_H
