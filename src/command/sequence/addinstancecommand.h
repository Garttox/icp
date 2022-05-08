/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file addinstancecommand.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef ADDINSTANCECOMMAND_H
#define ADDINSTANCECOMMAND_H

#include <command/command.h>
#include <model/umlinstancemodel.h>
#include <model/umlsequencemodel.h>

class AddInstanceCommand : public Command
{
public:
    AddInstanceCommand(UMLSequenceModel *umlSequenceModel, UMLInstanceModel *umlInstanceModel);

private:
    virtual void process() override;
    virtual void undo() override;

    UMLSequenceModel *umlSequenceModel;
    UMLInstanceModel *umlInstanceModel;
};

#endif // ADDINSTANCECOMMAND_H
