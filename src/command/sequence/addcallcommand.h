/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file addcallcommand.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef ADDCALLCOMMAND_H
#define ADDCALLCOMMAND_H

#include <command/command.h>

#include <model/umlsequencemodel.h>

/**
 * @brief Extends Command to implement adding new UML Call.
 * @author Michal Trlica (xtrlic02)
 */
class AddCallCommand : public Command
{
public:
    AddCallCommand(UMLSequenceModel *umlSequenceModel, UMLCallModel *umlCallModel);

private:
    virtual void process() override;
    virtual void undo() override;

    UMLSequenceModel *umlSequenceModel;
    UMLCallModel *umlCallModel;
};

#endif // ADDCALLCOMMAND_H
