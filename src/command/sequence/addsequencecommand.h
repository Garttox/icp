/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file addsequencecommand.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef ADDSEQUENCECOMMAND_H
#define ADDSEQUENCECOMMAND_H

#include <command/command.h>

#include <model/umlsequencemodel.h>

/**
 * @brief Extends Command to implement adding new UML Sequence.
 * @author Michal Trlica (xtrlic02)
 */
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
