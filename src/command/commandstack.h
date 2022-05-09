/**
 * ICP - UML Application
 * @date 6/5/2022
 * @file commandstack.h
 * @author Martin Bednář (xbedna77)
 */

#ifndef COMMANDSTACK_H
#define COMMANDSTACK_H

#include <QList>
#include "command.h"

/**
 * @brief Class storing commands of the app with ability to process and undo them.
 */
class CommandStack : protected QList<Command*>
{
public:
    CommandStack();
    ~CommandStack();

    /**
     * @brief Pushes command onto a stack and processes it.
     * @param command Command to process and push.
     */
    void push(Command *command);

    /**
     * @brief Undo the top command on the stack.
     */
    void undo();

    /**
     * @brief Get the singleton instance of CommandStack
     * @return CommandStack& 
     */
    static CommandStack& getInstance();

private:
    void undoTopCommand();
    void removeBottomCommand();

    /**
     * @brief If size of stack exceed MAX_SIZE, then Commands on the bottom of the stack are removed.
     */
    static constexpr int MAX_SIZE = 8;

};

#endif // COMMANDSTACK_H
