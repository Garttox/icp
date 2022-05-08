/**
 * ICP - UML Application
 * @date 7/5/2022
 * @file editcallcommand.cpp
 * @author Michal Trlica (xtrlic02)
 */
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
