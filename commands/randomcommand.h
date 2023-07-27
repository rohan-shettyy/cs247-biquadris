#ifndef RANDOMCOMMAND_H
#define RANDOMCOMMAND_H

#include "command.h"

class RandomCommand : public Command
{
public:
    RandomCommand();
    void Call(Board &board, string file = "") override;
};

#endif
