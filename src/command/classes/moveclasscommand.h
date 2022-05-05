#ifndef MOVECLASSCOMMAND_H
#define MOVECLASSCOMMAND_H

#include <QPoint>
#include "command/command.h"
#include "model/umlclassdata.h"


class MoveClassCommand : public Command
{
public:
    MoveClassCommand(UMLClassData *umlClassData, QPoint newPosition);

private:
    virtual void process() override;
    virtual void undo() override;

    QPoint oldPosition;
    QPoint newPosition;
    UMLClassData *umlClassData;
};

#endif // MOVECLASSCOMMAND_H
