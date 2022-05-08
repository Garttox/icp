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
