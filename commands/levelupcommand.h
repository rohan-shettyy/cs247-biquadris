#ifndef LEVELUPCOMMAND_H
#define LEVELUPCOMMAND_H

#include "command.h"

class LevelUpCommand : public Command
{
public:
    LevelUpCommand();
    void Call(Board &board) override;
};

#endif

