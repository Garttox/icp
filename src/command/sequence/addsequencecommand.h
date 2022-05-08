#ifndef ADDSEQUENCECOMMAND_H
#define ADDSEQUENCECOMMAND_H

#include <command/command.h>

#include <model/umlsequencemodel.h>

class AddSequenceCommand : public Command
{
public:
    AddSequenceCommand(UMLSequenceModel *const umlSequenceModel);
private:
    virtual void process() override;
    virtual void undo() override;

    UMLSequenceModel *const umlSequenceModel;
};

#endif // ADDSEQUENCECOMMAND_H
