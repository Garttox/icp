#include "commandstack.h"

CommandStack::CommandStack()
{}

void CommandStack::push(Command *command)
{
    if (size() == MAX_SIZE)
    {
        removeBottomCommand();
    }
    append(command);
    command->process();
}


void CommandStack::undo()
{
    if (size() > 0)
    {
        undoTopCommand();
    }
}

CommandStack& CommandStack::getInstance()
{
    static CommandStack stack;
    return stack;
}


// - - - - - private - - - - -

void CommandStack::undoTopCommand()
{
    Command *command = takeLast();
    command->undo();
    delete command;
}

void CommandStack::removeBottomCommand()
{
    Command *command = takeFirst();
    delete command;
}