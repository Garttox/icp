#include "editcallcommand.h"

EditCallCommand::EditCallCommand(UMLCallModel *umlCallModel, UMLMethodModel *newMethod, bool newAsync, int newDuration)
    : umlCallModel(umlCallModel), newMethod(newMethod), oldMethod(umlCallModel->getMethod()),
      newAsync(newAsync), oldAsync(umlCallModel->getAsync()), newDuration(newDuration),
      oldDuration(umlCallModel->getDuration())
{}

void EditCallCommand::process()
{
    umlCallModel->setDuration(newDuration);
    umlCallModel->setAsync(newAsync);
    umlCallModel->setMethod(newMethod);
}

void EditCallCommand::undo()
{
    if(oldMethod)
    {
        umlCallModel->setDuration(oldDuration);
        umlCallModel->setAsync(oldAsync);
        umlCallModel->setMethod(oldMethod);
    }
}
