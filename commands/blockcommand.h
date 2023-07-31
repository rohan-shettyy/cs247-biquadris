#ifndef BLOCKCOMMAND_H
#define BLOCKCOMMAND_H

#include "command.h"

class BlockCommand : public Command
{
    char type;
public:
    BlockCommand(char type);
    void Call(Board &board) override;
};

#endif
