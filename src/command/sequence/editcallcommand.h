/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file editcallcommand.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef EDITCALLCOMMAND_H
#define EDITCALLCOMMAND_H

#include <command/command.h>

#include <model/umlcallmodel.h>

class EditCallCommand : public Command
{
public:
    EditCallCommand(UMLCallModel *umlCallModel, UMLMethodModel *newMethod, bool newAsync, int newDuration);
private:
    virtual void process() override;
    virtual void undo() override;

    UMLCallModel *umlCallModel;
    UMLMethodModel *newMethod;
    UMLMethodModel *oldMethod;
    bool newAsync;
    bool oldAsync;
    int newDuration;
    int oldDuration;
};

#endif // EDITCALLCOMMAND_H
