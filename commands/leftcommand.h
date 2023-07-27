#ifndef LEFTCOMMAND_H
#define LEFTCOMMAND_H

#include "command.h"

class LeftCommand : public Command
{
public:
    LeftCommand();
    void Call(Board &board, string file = "") override;
};

#endif
