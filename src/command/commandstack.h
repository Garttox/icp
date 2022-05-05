#ifndef COMMANDSTACK_H
#define COMMANDSTACK_H

#include <QList>
#include "command.h"

/**
 * @brief Class storing commands of the app with ability to process and undo them.
 */
class CommandStack : private QList<Command*>
{
public:
    CommandStack();

    /**
     * @brief Pushes command onto a stack and processes it.
     * @param command Command to process and push.
     */
    void push(Command *command);

    /**
     * @brief Undo the top command on the stack.
     */
    void undo();

    static CommandStack& getInstance();

private:
    void undoTopCommand();
    void removeBottomCommand();

    static constexpr int MAX_SIZE = 8;

};

#endif // COMMANDSTACK_H
