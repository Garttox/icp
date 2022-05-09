/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file moveinstancecommand.h
 * @author Michal Trlica (xtrlic02)
 */
#ifndef MOVEINSTANCECOMMAND_H
#define MOVEINSTANCECOMMAND_H

#include <command/command.h>
#include <model/umlinstancemodel.h>
#include <model/umlsequencemodel.h>

#include <QPoint>

/**
 * @brief Extends Command to implement position change of UML Instance.
 * @author Michal Trlica (xtrlic02)
 */
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
