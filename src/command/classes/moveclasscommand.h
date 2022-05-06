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
