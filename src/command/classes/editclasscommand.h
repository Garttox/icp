#ifndef EDITCLASSCOMMAND_H
#define EDITCLASSCOMMAND_H

#include "command/command.h"
#include "model/umlclassmodel.h"

class EditClassCommand : public Command
{
public:
    EditClassCommand(UMLClassModel *umlClassModel, UMLClassModel *umlClassModelEdited);

private:
    virtual ~EditClassCommand();
    virtual void process() override;
    virtual void undo() override;

    UMLClassModel *umlClassModel;
    UMLClassModel *umlClassModelOld;
    UMLClassModel *umlClassModelEdited;
};

#endif // EDITCLASSCOMMAND_H
