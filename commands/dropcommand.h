#ifndef DROPCOMMAND_H
#define DROPCOMMAND_H

#include "command.h"

class DropCommand : public Command
{
public:
    DropCommand();
    void Call(Board &board, string file = "") override;
};

#endif
