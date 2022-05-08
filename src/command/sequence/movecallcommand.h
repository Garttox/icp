#ifndef MOVECALLCOMMAND_H
#define MOVECALLCOMMAND_H

#include <command/command.h>
#include <model/umlcallmodel.h>

class MoveCallCommand : public Command
{
public:
    MoveCallCommand(UMLCallModel *umlCallModel, int newAtTime);
private:
    virtual void process() override;
    virtual void undo() override;

    UMLCallModel *umlCallModel;
    int newAtTime;
    int oldAtTime;
};

#endif // MOVECALLCOMMAND_H
