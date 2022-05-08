#ifndef MOVEINSTANCECOMMAND_H
#define MOVEINSTANCECOMMAND_H

#include <command/command.h>
#include <model/umlinstancemodel.h>
#include <model/umlsequencemodel.h>

#include <QPoint>

class MoveInstanceCommand : public Command
{
public:
    MoveInstanceCommand(UMLInstanceModel *umlInstanceModel, int newPosX);
private:
    virtual void process() override;
    virtual void undo() override;

    int oldPosX;
    int newPosX;
    UMLInstanceModel *umlInstanceModel;
};

#endif // MOVEINSTANCECOMMAND_H
