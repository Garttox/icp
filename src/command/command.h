#ifndef COMMAND_H
#define COMMAND_H

/**
 * @brief Command class provides uniform way of manipulating app state.
 */
class Command
{
protected:
    virtual ~Command();

private:
    virtual void process() = 0;
    virtual void undo() = 0;

    friend class CommandStack;
};

#endif // COMMAND_H