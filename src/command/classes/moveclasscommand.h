/**
 * ICP - UML Application
 * @date 6/5/2022
 * @file moveclasscommand.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef MOVECLASSCOMMAND_H
#define MOVECLASSCOMMAND_H

#include <QPoint>
#include "command/command.h"
#include "model/umlclassmodel.h"


class MoveClassCommand : public Command
{
public:
    MoveClassCommand(UMLClassModel *umlClassModel, QPoint newPosition);

private:
    virtual void process() override;
    virtual void undo() override;

    QPoint oldPosition;
    QPoint newPosition;
    UMLClassModel *umlClassModel;
};

#endif // MOVECLASSCOMMAND_H
