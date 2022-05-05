#ifndef EDITCLASSCOMMAND_H
#define EDITCLASSCOMMAND_H

#include "command/command.h"
#include "model/umlclassdata.h"

class EditClassCommand : public Command
{
public:
    EditClassCommand(UMLClassData *umlClassData, UMLClassData *umlClassDataEdited);

private:
    virtual ~EditClassCommand();
    virtual void process() override;
    virtual void undo() override;

    UMLClassData *umlClassData;
    UMLClassData *umlClassDataOld;
    UMLClassData *umlClassDataEdited;
};

#endif // EDITCLASSCOMMAND_H
