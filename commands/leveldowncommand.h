#ifndef LEVELDOWNCOMMAND_H
#define LEVELDOWNCOMMAND_H

#include "command.h"

class LevelDownCommand : public Command
{
public:
    LevelDownCommand();
    void Call(Board &board) override;
};

#endif

