#ifndef MOVEINSTANCECOMMAND_H
#define MOVEINSTANCECOMMAND_H

#include <command/command.h>
#include <model/umlinstancemodel.h>
#include <model/umlsequencemodel.h>

#include <QPoint>

class MoveInstanceCommand : public Command
{
public:
    MoveInstanceCommand(UMLInstanceModel *umlInstanceModel, QPoint newLocation);
private:
    virtual void process() override;
    virtual void undo() override;

    QPoint newLocation;
    QPoint oldLocation;
    UMLInstanceModel *umlInstanceModel;
};

#endif // MOVEINSTANCECOMMAND_H
