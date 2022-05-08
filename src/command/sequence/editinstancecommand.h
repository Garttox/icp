/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file editinstancecommand.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef EDITINSTANCECOMMAND_H
#define EDITINSTANCECOMMAND_H

#include <command/command.h>

#include <model/umlsequencemodel.h>

class EditInstanceCommand : public Command
{
public:
    EditInstanceCommand(UMLInstanceModel *umlInstanceModel, QString newName);

private:
    virtual void process() override;
    virtual void undo() override;

    UMLInstanceModel *umlInstanceModel;
    QString newName;
    QString oldName;
};

#endif // EDITINSTANCECOMMAND_H
